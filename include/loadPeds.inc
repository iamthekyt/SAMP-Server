#define MAX_PEDESTRIANS     8
#define MAX_NODES           8

enum e_Ped
{
	Float:movingTo[3],
	node,
	run
}

new Ped[MAX_PEDESTRIANS][e_Ped];
new Float:nodes[MAX_NODES][3];
new nodeConnections[MAX_NODES][4];//n, s, e, o



forward UpdatePedrestiansMove();
forward ChangePedRoute(pedid, reason);
forward IsPedInRangeOf(pedid, Float:x, Float:y, Float:z, Float:range);

//Extended actor functions by Emmet
stock static PreloadActorAnimations(actorid)
{
	for(new i = 0; i < sizeof(s_AnimationLibraries); i ++)
	{
	    ApplyActorAnimation(actorid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
	}
}

stock loadNodes()
{
    new File:handle = fopen("nodes.txt", io_read), buf[256],
			tmp_node[3][32], i = 0, x;
	if(handle)
	{
		while(fread(handle, buf))
		{
			split(buf, tmp_node, ',');
			for(x = 0; x < 3; x++)
			{
				nodes[i][x] = floatstr(tmp_node[x]);
			}
			i++;
		}
		fclose(handle);
		printf("The file \"nodes.txt\" was found and %d nodes are loaded.", i);
	}
	else
	{
		print("The file \"nodes.txt\" does not exists, or can't be opened.");
	}
}

stock loadNodesConnections()
{
	new File:handle = fopen("nodesConnections.txt", io_read), buf[128], tmp_node[2][3],
		i = -1, n, last_node = -1, node_changed[MAX_NODES] = {0};
	if(handle)
	{
	    for(new a = 0; a < MAX_NODES; a++)
	    {
	    	nodeConnections[a][0] = nodeConnections[a][1] =
 			nodeConnections[a][2] = nodeConnections[a][3] = -1;
	    }
	
		while(fread(handle, buf))
		{
			split(buf, tmp_node, ',');
			if(strval(tmp_node[0]) == last_node) {
				n = strval(tmp_node[1]);
				nodeConnections[i][node_changed[i]++] = n;
				nodeConnections[n][node_changed[n]++] = i;
			}
			else {
				n = strval(tmp_node[1]);
				last_node = i = strval(tmp_node[0]);
				nodeConnections[i][node_changed[i]++] = n;
				nodeConnections[n][node_changed[n]++] = i;
			}
		}
		fclose(handle);
		printf("The file \"nodesConnections.txt\" was found and %d connections are loaded.", i);
	}
	else
	{
		print("The file \"nodesConnections.txt\" does not exists, or can't be opened.");
	}
	
	for(new h = 0; h < MAX_NODES; h++)
	{
	    printf("%d, %d, %d, %d", nodeConnections[h][0], nodeConnections[h][1],
								nodeConnections[h][2], nodeConnections[h][3]);
	}
}

stock createPedestrians()
{
    new p;
	for(p = 0; p < MAX_PEDESTRIANS; p++)
	{
		CreateActor(random(300), nodes[p][0], nodes[p][1], nodes[p][2], 0.0);
		Ped[p][run] = 0;
		Ped[p][node] = p;
		Ped[p][movingTo][0] = nodes[p][0];
		Ped[p][movingTo][1] = nodes[p][1];
		Ped[p][movingTo][2] = nodes[p][2];
	}
	SetTimer("UpdatePedrestiansMove", 1000, true);
	for(p = 0; p < MAX_PEDESTRIANS; p++)
	{
	    PreloadActorAnimations(p);
	    ApplyActorAnimation(p, "ped", "WALK_civi", 4.1, 1, 1, 1, 0, 0);
	    SetActorInvulnerable(p, false);
	}
}


public UpdatePedrestiansMove()
{
	for(new p = 0; p < MAX_PEDESTRIANS; p++)
	{
	    if(Ped[p][run] != 0) continue;
	
	    if(IsPedInRangeOf(p, Ped[p][movingTo][0], Ped[p][movingTo][1], Ped[p][movingTo][2], 1))
	    {
	        new nextNode, nodeDirection, Float:angle, Float:x, Float:y;
	        do
	        {
				nodeDirection = random(4);
				
			} while(nodeConnections[Ped[p][node]][nodeDirection] == -1);
			
			nextNode = nodeConnections[Ped[p][node]][nodeDirection];
			x = nodes[Ped[p][node]][0] - nodes[nextNode][0];
			y = nodes[Ped[p][node]][1] - nodes[nextNode][1];
			angle = atan2(x, y);
			
			SetActorFacingAngle(p, angle);
	    }
	}
}

public ChangePedRoute(pedid, reason)
{

}

public IsPedInRangeOf(pedid, Float:x, Float:y, Float:z, Float:range)
{
	new Float:xx, Float:yy, Float:zz, Float:dist;
	GetActorPos(pedid, xx, yy, zz);
	
	xx -= x;
	yy -= y;
	zz -= z;
	
	dist = xx*xx + yy*yy + zz*zz;
	
	if(dist <= range*range)
	    return 1;
	else
		return 0;
}