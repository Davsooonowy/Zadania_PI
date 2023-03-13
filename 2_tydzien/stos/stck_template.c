#include <stdio.h>

#define STACK_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

int stack[STACK_SIZE];
int top = 0;

int stack_push(int x) {
    if (top >= STACK_SIZE-1) {
        return OVERFLOW;
    } else {
        stack[top++] = x;
        return OK;
    }
}

int stack_pop(void) {
    if(top < 0) {
        return UNDERFLOW;
    } else {
        int val = stack[top];
        top--;
        return val;
    }

}

int stack_state(void) {
    return top;
}

// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

int queue_push(int in_nr) {
    if(in_nr + in > 10){
        int temp = in_nr + in - 10;
        while(in < 10){
            queue[in++]=curr_nr++;
        }
        for(int i = 0; i < temp; i++)
            curr_nr++;
        return OVERFLOW;
    }
    else{
        for(int i = 0; i < in_nr; i++){
            queue[in++]=curr_nr++;
        }
        return OK;
    }
}

int queue_pop(int out_nr) {
    if(out_nr > in)
    {
        in=0;
        return UNDERFLOW;
    }
    else{
        for(int i = out_nr; i < in; i++)
            queue[i - out_nr]= queue[i];
        in = in - out_nr;
    }
    return in;
}

int queue_state() {
    return in;
}

void queue_print() {
    for(int i = 0; i < in; i++) {
        printf("%d ",queue[i]);
    }
}


// Queue with cyclic buffer

#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out = 0, len = 0;


int cbuff_push(int cli_nr) {
    if(len == 10){
        return OVERFLOW;
    }
    if(len + out > 9){
        cbuff[(out + len) % 10] = cli_nr;
    }
    else{
        cbuff[len + out] = cli_nr;
    }
    len++;
    return OK;
}


int cbuff_pop(void) {
    if(len == 0){
        return UNDERFLOW;
    }
    else{
        len--;
        int temp = cbuff[out];
        if(out != 10){
            out += 1;
        }
        else{
            out = len % 10;
        }
        return temp;
    }
}

int cbuff_state(void) {
    return len;
}

void cbuff_print(void) {
    for(int i = 0; i < len; i++){
        printf("%d ", cbuff[(out+i)%10]);
    }
}

int main(void) {
	int to_do, n, client_no, answer;
	scanf("%d", &to_do);
	switch(to_do) {
		case 1: // stack
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = stack_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", stack_pop());
				} else printf("%d", stack_state());
			} while(n != 0);
			break;
		case 2: // FIFO queue with shifts
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = queue_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					if ((answer = queue_pop(-n)) < 0) printf("%d ", answer);
				} else {
					printf("\n%d\n", queue_state());
					queue_print();
				}
			} while(n != 0);
			break;
		case 3: // queue with cyclic buffer
			client_no = 0;
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = cbuff_push(++client_no)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", cbuff_pop());
				} else {
					printf("\n%d\n", cbuff_state());
					cbuff_print();
				}
			} while(n != 0);
			break;
		default:
			printf("NOTHING TO DO!\n");
	}
	return 0;
}