#pragma once

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

int mx_strcmp(const char *s1, const char *s2);
int mx_strlen(char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
char *mx_strcpy(char *dst, const char *src);
char *mx_strnew(const int size);
int number_length(int number);
char *mx_itoa(int number);
bool mx_isspace(char c);
bool mx_isdigit(int c);
int mx_atoi(const char *str);
char *mx_str_append(char *str, char symbol);
