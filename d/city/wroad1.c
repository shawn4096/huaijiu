// /d/city/wroad1.c

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
大道往西进入安徽境内。东边通向扬州城。
LONG
	);
        set("outdoors", "扬州");

	set("exits", ([
		"east" : __DIR__"ximen",
                "west" : __DIR__"wroad2",
                "northwest" : __DIR__"winmo",
	]));

   	set("coor/x",60);
  	set("coor/y",0);
   	set("coor/z",0);
   	setup();
}

void init()
{	
	object me=this_player();
	
	if ( me->query("family/family_name") == "丐帮" 
	    && userp(me)
	    &&!me->query("gb/alloted")){
		if (me->query("family/master_name")== "奚长老"
		  ||me->query("family/master_name")== "空空儿"){
			me->set("gb/fenduo","大勇分舵");
			me->set("gb/alloted",1);
			return;
		}
		if (me->query("family/master_name")== "吴长老"
		  || me->query("family/master_name")== "蒋舵主"){
			me->set("gb/fenduo","大信分舵");
			me->set("gb/alloted",1);
			return;
		}
		if (me->query("family/master_name")== "白世镜"){
			me->set("gb/fenduo","刑堂");
			me->set("gb/alloted",1);
			return;
		}
		me->set("gb/fenduo","大勇分舵");
		me->set("gb/alloted",1);
		return;
	}
}		
