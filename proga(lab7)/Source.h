unsigned long long int hashing(char* key);
void show_history(unsigned long long int account);
double get_percent(int sum, const char* from, const char* to);
char* to_string(unsigned long long int account);
void get_balance(struct List* list, unsigned long long int account_number);
void get_money(struct List* list, unsigned long long int account_number, int sum);
void transfer(struct List* list, unsigned long long int from, unsigned long long int to, int sum);
void put_money(struct List* list, unsigned long long int account_number, int sum);
