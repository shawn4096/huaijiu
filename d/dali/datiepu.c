// Room: /dali/datiepu.c
// bbb 1997/06/11
// Modify By River 98/12/	  
inherit ROOM;

void create()
{
	set("short", "打铁铺");
	set("long", @LONG
这里是一间打铁铺子，从火炉中冒出的火光将墙壁映得通红，屋子的角落
里堆满了各式铁器的完成品或未完成品，像是锄头、铁锤、铲子等，叮叮当当
的声音敲得满屋子响。
LONG
	);
	set("exits", ([ 
             "east" : __DIR__"nanjie1",
        ]));

	set("objects", ([
		__DIR__"npc/tiejiang": 1,
        ]));
	set("coor/x",-340);
  set("coor/y",-460);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/datiepu",1);
      }
}
