typedef void* DATE; //Handle type

enum status { FAILURE, SUCCESS };
typedef enum status Status;

DATE date_init_default(void);

//accessor functions

int date_get_day(DATE hDate);
int date_get_month(DATE hDate);
int date_get_year(DATE hDate);
char* date_get_month_name(DATE hDate);

//mutator functions
Status date_set_day(DATE hDate, int day);

void date_output(DATE hDate);

void date_destroy(DATE* phDate); // cleans up any memory
