int SCN (
	info_t * info,
	const int shipID) {
		
	if(info->shipKerosen[shipID] < 3)
	{
		NON(info, shipID);
		return -2;
	}
	
	int i, k;
	int min = 21, nbShipsTrouver, distance, id = -1;
	int* list = NULL;
	int dist = info->nmap->size.x + info->nmap->size.y + 1;
	
	for(k = 1; k < dist; k++)
	{
		
		list = rect_getTargets(info->nmap, info->nmap->shipPosition[shipID], k, &nbShipsTrouver);
		
		if(nbShipsTrouver > 0)
		{
			id = list[i];
			k = dist;
		}
	}
	free(list);
	
	// Affichage
	printf("  - J%d utlise le radar ->", shipID);
	if(id != -1)
	{
		printf(" ennemie trouvé en (%d,%d) avec %d C\n", info->nmap->shipPosition[id].x, info->nmap->shipPosition[id].y, info->shipCoque[id]);
		return id;
	}
	else
	{
		printf(" aucun joueur trouvé\n");
		return -1;
	}
}
