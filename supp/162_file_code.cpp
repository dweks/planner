int menuLoad(Activity array[])
{
	int cyc = 0; // cycler for struct indeces

	ifstream loadFile;
	loadFile.open("favorite.txt");

	if(loadFile) // Check if favorite.txt has been opened
	{
		// If favorite.txt is open, get each member of each saved struct
		loadFile.get(array[cyc].name, NAME, '#');
		loadFile.ignore(100, '#');
	
		while(!loadFile.eof() && cyc < STRUC)
		{
			loadFile.get(array[cyc].loc, LOC, '#');
			loadFile.ignore(100, '#');

			loadFile.get(array[cyc].time, TIME, '#');
                        loadFile.ignore(100, '#');
			
			loadFile.get(array[cyc].desc, DESC, '#');
			loadFile.ignore(100, '#');
			
			loadFile.get(array[cyc].exp, EXP, '#');
                        loadFile.ignore(100, '#');
			
			loadFile.get(array[cyc].req, REQ, '#');
			loadFile.ignore(100, '#');
			
			loadFile.get(array[cyc].lim, LIM, '\n');
                        loadFile.ignore(100, '\n');
			
			++cyc; // will cycle to next activity

			// Attempt to read in the next activity
			loadFile.get(array[cyc].name, NAME, '#');
                        loadFile.ignore(100, '#');
		}

		loadFile.close();
		
		cout << "\n\n> FILE LOADED <\n\n";
		
		cont();
	}
	
	
	// If favorite.txt is not found, show error message
	else if(!loadFile)
	{
		cout 
		<< "\n> FILE NOT FOUND <\n\n"
		<< "Please replace the favorite.txt file or create new entries.\n\n"
		;

		cont();
	}
