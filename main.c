/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : main.c                                  	    		 */
/* Date          : May 13, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "APP/app.h"



int main(){
	app_init();
	CFG_Direction();
	app_main();
	while(1);
	return 0;
}
