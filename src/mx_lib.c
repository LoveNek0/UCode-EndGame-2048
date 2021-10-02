#include "mx_lib.h"

int mx_strcmp(const char *s1, const char *s2){
    for (; *s1 == *s2; ++s1, ++s2)
        if (*s2 == '\0')
            return 0;
    return *s1 - *s2;
}

int mx_strlen(char *s){
	 int size = 0;
	 for(char *i = s; *i != '\0'; i++)
		 size++;
	 return size;
}
void mx_swap_char(char *s1, char *s2) {
    char s3 = *s1;
    *s1 = *s2;
    *s2 = s3;
}

void mx_str_reverse(char *s) {
    int len = mx_strlen(s) - 1;
    
    if (s)
        for (int i = 0; i <= len / 2; i++)
            mx_swap_char(&s[i], &s[len - i]);
}

char *mx_strcpy(char *dst, const char *src) {
    int i = 0;
    
    while (src[i]) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

char *mx_strnew(const int size) {
    char *memory = NULL;
    int i = 0;

    if (size < 0)
        return NULL;
    memory = (char *)malloc((size + 1) * sizeof(char));
    while (i < size) {
        memory[i] = '\0';
        i++;
    }
    memory[i] = '\0';
    return memory;
}

int number_length(int number) {
	int length = 0;

	while (number) {
		number /= 10;
		length++;
	}
	return length;
}

char *mx_itoa(int number) {
	int length = number_length(number);
	int tmp = number;
	char *result = NULL;

	result = mx_strnew(length);
	if (number == 0)
		return mx_strcpy(result, "0");
	if (number == -2147483648)
		return mx_strcpy(result, "-2147483648");
	tmp = number;
	for (int i = 0; i < length; i++) {
		if (tmp < 0) {
			result[length] = '-';
			tmp = -tmp;
		}
		result[i] = (tmp % 10) + '0';
		tmp /= 10;
	}
	mx_str_reverse(result);
	return result;
}

bool mx_isspace(char c) {
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == 'r')
        return true;
    return false;
}

bool mx_isdigit(int c) {
    if (c > 47 && c < 59)
        return true;
    return false;
}

int mx_atoi(const char *str) {
    int result = 0;
    bool sign = false;
    if(*str) {
        while(mx_isspace(*str))
            str++;
        if (*str == '-') {
            sign = true;
            str++;   
        }
        else if (*str == '+')
            str++; 
        while (mx_isdigit(*str)) {
            result *= 10;
            if (sign)
                result -= *str-48;
            else
                result += *str-48;
            str++;
        }
    }
    return result;
}

char *mx_str_append(char *str, char symbol){
	int size = mx_strlen(str) + 1;
	char *s = mx_strnew(size);
	for(int i = 0; i < size; i++)
		if(i == size - 1)
			s[i] = symbol;
		else 
			s[i] = str[i];
	return s;
}
