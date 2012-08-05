#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

/* Basic brainfuck interpreter
 *
 * A simple brainfuck interpreter with a stack to keep track of loop positions
 *
 */

/* Stack item */
struct ll {
    int pos;
    int line;
    struct ll* prev;
};

/* Top of the stack */
struct ll* top;

/* push an item onto the stack */
void ll_push(int pos, int line){
    struct ll* cur = (struct ll*)malloc(sizeof(ll));
    if(top) cur->prev = top;
    top = cur;
    top->pos = pos;
    top->line = line;
}

/* pop an item off of the stack */
struct ll* ll_pop(){
    struct ll* x = top;
    if(top) top = top->prev;
    return x;
}

/* Get the top of the stack without popping it */
struct ll* ll_peek(){
    return top;
}

/* Remove item from stack without returning it */
void ll_del(){
    struct ll* st = ll_pop();
    if(st) free(st);
}

/* Debug print of stack contents */
void print_stack(){
    struct ll* x = top;
    while(x){
        printf("%d, %d\n", x->line, x->pos);
        x = x->prev;
    }
    printf("End stack\n");
}

int main(int argc, char** argv){
    if(argc == 1){ 
        printf("Please specify input file\n");
        exit(1);
    }

    FILE* f = fopen(argv[1], "r");
    
    if(!f){
        printf("File not found: %s\n", argv[1]);
        exit(1);
    }

    int pc = 0; /* Position in stream of current instruction */
    
    char mem[1024]; /* Memory array */
    char* dp = mem; /* Data pointer */

    bool debug = false;
    int line = 1;

    for(int i=0; i < 1024; ++i) mem[i] = 0;
    int c;
    do{
        c = getc(f); pc++;
        if (debug) printf("Character: %c, line: %d\n", c, line);
        switch(c){
            case 10: /* Newline */
                if(debug) printf("Line %d\n", line);
                line += 1; break;
            case 62: /* > */
                dp++; break;
            case 60: /* < */
                dp--; break;
            case 43: /* + */
                (*dp)++; break;
            case 45: /* - */
                (*dp)--; break;
            case 46: /* . */
                if(debug) printf("Print statement: %d\n", line);
                printf("%c", *dp); break;
            case 44: /* , */
                (*dp) = getchar(); break;
            case 91: /* [ */
                if(*dp == 0){ /* If pointer is zero, find matching closing bracket */
                    int depth = 1;
                    do{
                        c = getc(f); pc++;
                        if(debug){ 
                            printf("depth = %d\n", depth);
                            printf("%c", c);
                        }
                        if(c == 91) depth += 1;
                        else if(c == 93) depth -=1;
                        else if(c == 10) line += 1;
                        else if(c == EOF){
                            printf("Unmatched bracket at %d", top->pos);
                            exit(1);
                        }
                    } while(depth != 0);
                }
                else{ /* else push the position onto the stack and move to next instruction */
                    ll_push(pc, line);
                    if(debug){
                        printf("[ not taken\n");
                        print_stack();
                    }
                }
                break;
            case 93: /* ] */
                if(*dp){ /* Loop back to beginning, but don't remove loop start point from stack */
                    struct ll* st = ll_peek();
                    pc = st->pos;
                    line = st->line;
                    fseek(f, pc, SEEK_SET);
                }
                else{ /* Finished looping, remove loop start from stack */
                    ll_del();
                    if(debug){
                        printf("Popped stack");
                        print_stack();
                    }
                }
                break;
        }

    } while (c!=EOF);
    printf("\n");
}
