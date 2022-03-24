#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_INT,TK_HEX,TK_REG

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"\\-", '-'},         // subtract
  {"\\*", '*'},         // multiply
  {"/", '/'},         // devide
  {"\\(", '('},         // left bracket
  {"\\)", ')'},         // right bracket
  {"==", TK_EQ},        // equal
	{"0x[0-9a-fA-F]+",TK_HEX},//HEX
  {"[0-9]+",TK_INT},     //integer
	{"\\$[a-z0-9]+",TK_REG},  //register
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //     i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
      	  case '+': tokens[nr_token].type='+';nr_token++;break;
          case '-': tokens[nr_token].type='-';nr_token++;break;
          case '*': tokens[nr_token].type='*';nr_token++;break;
          case '/': tokens[nr_token].type='/';nr_token++;break;
          case '(': tokens[nr_token].type='(';nr_token++;break;
          case ')': tokens[nr_token].type=')';nr_token++;break;
          case TK_NOTYPE: break;
				  case TK_EQ:tokens[nr_token].type=TK_EQ;nr_token++;break;
				  case TK_INT:tokens[nr_token].type=TK_INT;
											strncpy(tokens[nr_token].str,substr_start,substr_len);
											tokens[nr_token].str[substr_len]='\0';
											nr_token++;
											break;
          case TK_HEX:tokens[nr_token].type=TK_HEX;
                      strncpy(tokens[nr_token].str,substr_start,substr_len);
                      tokens[nr_token].str[substr_len]='\0';
                      nr_token++;
                      break;
          case TK_REG:tokens[nr_token].type=TK_REG;
                      strncpy(tokens[nr_token].str,substr_start,substr_len);
                      tokens[nr_token].str[substr_len]='\0';
                      nr_token++;
                      break;
          default: TODO();
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}
/******************get value function******************/
void show_token();
uint32_t eval(int p,int  q); 
bool check_parentheses(int p,int q);
int findop(int p,int q);
/******************************************************/

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  //show_token();
	//return 0;

  /* TODO: Insert codes to evaluate the expression. */
	*success=true;
	uint64_t x=eval(0,nr_token-1);
	return x;
  //TODO();
}

void show_token()
{
  int i;
  for (i=0;i<nr_token;i++)
  {
    printf("show tokens:\n");
    if(tokens[i].type==TK_INT)
    printf("%d %s\n",tokens[i].type,tokens[i].str);
    else printf("%d\n",tokens[i].type);
  }
}


uint32_t eval(int p,int  q) {
  if (p > q) {
    /* Bad expression */
    printf("Bad expression!");
    assert(0);
    return 0;
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
		uint64_t x;
		bool success=0;
	  switch (tokens[p].type)
    {
			case TK_INT: x=strtol(tokens[p].str,NULL,10);return x;break;
			case TK_HEX: x=strtol(tokens[p].str,NULL,16);return x;break;
			case TK_REG: x=isa_reg_str2val(tokens[p].str,&success);
								   if(!success) printf("error reg name!!");
									 return x; break;
		}
  }
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }
  else {
    /* We should do more things here. */
		 
		int op=findop(p,q);
    uint64_t val1 = eval(p, op - 1);
    uint64_t val2 = eval(op + 1, q);

    switch (tokens[op].type) {
      case '+':  return val1 + val2;
      case '-':  return val1 - val2;
      case '*':  return val1 * val2;
      case '/':  return val1 / val2;
			case TK_EQ:  return val1 == val2;
      default: assert(0);
    }
  }
	return 0;
}
 
int findop(int p,int q)
{
	int i;
	int flag=0;
	int op=p;
	for(i=p;i<=q;i++)
	{
		switch (tokens[i].type)
		{
			case TK_INT: continue;
			case '(': 
								while(tokens[i].type!=')') i++;
								break;
			case ')': continue;
			case TK_EQ: if(flag<3) {flag=3;op=i;} break;
			case '+': case '-': if(flag<2) {flag=2;op=i;} break;
			case '*': case '/': if(flag<1) {flag=1;op=i;} break;
		}
	}
	return op;
}
bool check_parentheses(int p,int q)
{
		int flag=0;
		int i;
		if (tokens[p].type!='('||tokens[q].type!=')') return false;
		for(i=p+1;i<=q-1;i++)
		{
			if(tokens[i].type=='(')
			{
				flag++;
				if(i==q-1) return false;
				if(!((tokens[i+1].type=='(') ||( tokens[i+1].type==TK_INT))) return false;
			}
    	if(tokens[i].type==')')
			{
				flag--;
				if(flag<0) return false;
				if(i==p+1) return false;
				if(!(tokens[i-1].type==')' || tokens[i-1].type==TK_INT)) return false;
			}
		}
		if(flag!=0)
		{
			return false;	
		}
	return true;
}


