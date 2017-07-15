/*
* @Author: otae
* @Date:   2017-07-15 11:33:09
* @Last Modified by:   otae
* @Last Modified time: 2017-07-15 13:36:52
*/

void take_part_screenshot();
void take_screenshot();

int main(int ac, char **av) {
	if (ac > 1)
		take_part_screenshot();
	else
		take_screenshot();
}