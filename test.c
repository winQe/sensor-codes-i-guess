bool clockwise_circular_search_right_compass_check()
{
	int newvalue=0; //value after move right
	int ogvalue = read_compass(); //original value
    move_right(500);
	//clockwise_circular_search_right(500);
	while(newvalue!=ogvalue){
		newvalue = read_compass(); //after move right
		move_right(10);
	}
	
}