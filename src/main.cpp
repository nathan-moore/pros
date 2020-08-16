#include "main.h"

// not supposed to be exhastive, but provides a decent coverage

void trigTest()
{
    float input = 1.0;

    float aboutOne = atanf(tanf(sinf(asinf(input))));

    aboutOne = powf(2, log2f(aboutOne));

    if (aboutOne > .95 && aboutOne < 1.05)
        return;

    std::cout << "trig test isn't in expected range" << std::endl;
}

void trigDoubleTest()
{
    double input = 1.0;

    double aboutOne = atan(tan(sin(asin(input))));

    aboutOne = pow(2, log2(aboutOne));

    if (aboutOne > .95 && aboutOne < 1.05)
        return;

    std::cout << " double trig test isn't in expected range" << std::endl;
}

int cmp(void const* a, void const* b)
{
    return *(int*)a >= *(int*)b;
}

void miscTest()
{
    int arr[] = { 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    qsort(arr, sizeof(arr) / sizeof(int), sizeof(int), cmp);

    for (int i = 1; i < (sizeof(arr) / sizeof(int)); i++)
    {
        if (arr[i] < arr[i - 1])
            std::cout << "qsort didn't work" << std::endl;
    }
}

void fileIOTest()
{
    FILE* file = fopen("fileThatDoesntExist", "r");
    if (file == NULL)
        return;

    //atleast check that these link
    ftell(file);
    fwrite("Hello World, this is a test to make sure that this works", sizeof(char), 10, file);
    fscanf(file, "%d", NULL);
    fclose(file);

    std::cout << "fileIO opened a file that doesn't exist" << std::endl;
}

void stringTests() 
{
    const char* s = "This is a test string";
    char* mallocedString = strdup(s);
    int len = strlen(mallocedString);
    if (len != strlen(s))
        std::cout << "error" << std::endl;

    char* sub = strstr(mallocedString, "is");
    if (sub == NULL)
        std::cout << "strstr not working" << std::endl;
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	trigTest();
    trigDoubleTest();
    fileIOTest();
    miscTest();
	stringTests();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}
}
