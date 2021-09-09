
Uint32 pacAction(Uint32 interval, void* param)
{
	int* index = (int*)param;
	if (period_die) return interval;
	switch (pv.x + 2 * pv.y)
	{
	case 1:
		index[0] = (index[0] % 3 == 0) ? 1 : (index[0] % 3 == 1) ? 2 : 0;
		break;
	case -1:
		index[0] = (index[0] % 3 == 0) ? 4 : (index[0] % 3 == 1) ? 5 : 3;
		break;
	case -2:
		index[0] = (index[0] % 3 == 0) ? 7 : (index[0] % 3 == 1) ? 8 : 6;
		break;
	case 2:
		index[0] = (index[0] % 3 == 0) ? 10 : (index[0] % 3 == 1) ? 11 : 9;
		break;
	}
	return interval;
}

Uint32 pac2Action(Uint32 interval, void* param)
{
	int* index = (int*)param;
	if (period_die) return interval;
	switch (pv2.x + 2 * pv2.y)
	{
	case 1:
		index[0] = (index[0] % 3 == 0) ? 1 : (index[0] % 3 == 1) ? 2 : 0;
		break;
	case -1:
		index[0] = (index[0] % 3 == 0) ? 4 : (index[0] % 3 == 1) ? 5 : 3;
		break;
	case -2:
		index[0] = (index[0] % 3 == 0) ? 7 : (index[0] % 3 == 1) ? 8 : 6;
		break;
	case 2:
		index[0] = (index[0] % 3 == 0) ? 10 : (index[0] % 3 == 1) ? 11 : 9;
		break;
	}
	return interval;
}

Uint32 dieAction(Uint32 interval, void* param)
{
	int* index = (int*)param;
	index[0] = (index[0] + 1) % 13; // die
	return interval;
}

Uint32 die2Action(Uint32 interval, void* param)
{
	int* index = (int*)param;
	index[0] = (index[0] + 1) % 13; // die
	return interval;
}

Uint32 ghostAction(Uint32 interval, void* param)
{
	if (!pauseFlag)
	{
		int* index = (int*)param;
		for (int i = 0; i < 4; i++)
		{
			if ((!ghost_frightened[i] && !ghost_eaten[i]))
			{
				switch (gv[i].x + 2 * gv[i].y)
				{
				case 1:
					index[i] = (index[i] % 2 == 0) ? 1 : 0;
					break;
				case -2:
					index[i] = (index[i] % 2 == 0) ? 5 : 4;
					break;
				case -1:
					index[i] = (index[i] % 2 == 0) ? 3 : 2;
					break;
				case 2:
					index[i] = (index[i] % 2 == 0) ? 7 : 6;
					break;
				}
			}
			else
			{
				if ((dist(pacc, ghostc[i], l_char * l_grid) || dist(pacc2, ghostc[i], l_char * l_grid)) && ghost_eatening[i]) {
					index[i] = 15 + cnt;
				}
				else if (ghost_eaten[i] && !ghost_eatening[i])
				{
					switch (gv[i].x + 2 * gv[i].y)
					{
					case 1:
						index[i] = 12;
						break;
					case -2:
						index[i] = 13;
						break;
					case -1:
						index[i] = 14;
						break;
					case 2:
						index[i] = 15;
						break;
					}
				}
				else if (period_frightened_end)
				{
					switch (index[i])
					{
					case 8:
						index[i] = 11;
						break;
					case 9:
						index[i] = 8;
						break;
					case 10:
						index[i] = 9;
						break;
					case 11:
						index[i] = 10;
						break;
					}
				}
				else {
					index[i] = (index[i] % 2 == 0) ? 9 : 8;
				}
			}
		}
	}
	return interval;
}

Uint32 ghost_isolated_Action(Uint32 interval, void* param)
{
	for (int i = 0; i < 4; i++) {
		if (SDL_GetTicks() - time_isolated > time_ghost_isolated[i]) {
			ghost_isolated[i] = false;
		}
	}
	return interval;
}

Uint32 forward_view_Action(Uint32 interval, void* param)
{
	static double fi;
	/*
	if (pv.x == 0 && pv.y > 0) fi = 180;
	else if (pv.x == 0 && pv.y < 0) fi = 0;
	else if (pv.x < 0 && pv.y == 0) fi = 90;
	else if (pv.x > 0 && pv.y == 0) fi = 270;
	cout << fi << " " << theta << endl;
	*/
	fi = (dir - 90);
	double dif = fi - theta;
	if (dif > 180) dif -= 360;
	if (dif < -180) dif += 360;

	if (theta != fi) {
		//theta += dif / 20;
		if (dif<0.3 && dif>-0.3) theta += dif;
		else if (dif > 0)
			theta += dif / 15 + 0.3;
		else
			theta += dif / 15 - 0.3;
	}
	if (theta > 360) theta -= 360;
	else if (theta < 0) theta += 360;
	return interval;
}

Uint32 file_move_Action(Uint32 interval, void* param)
{

	static int dif;

	dif = fileaimpos - filepos;

	if (fileaimpos != filepos) {
		//theta += dif / 20;
		if (dif <= 1 && dif >= -1) filepos += dif;
		else if (dif > 0)
			filepos += dif / 10 +1;
		else if (dif<0)
			filepos += dif / 10 -1;
	}
	if (alpha > 0) alpha-=(800/(alpha-20)-1);
	if (alpha < 50) alpha = 0;
	return interval;
}



