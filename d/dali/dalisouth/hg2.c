// Room: /d/dali/hg2.c
// bbb 1997/06/10 
// cool 98.3.17
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "海埂南");
	set("long", @LONG
这里三面云山，一湖秀水，碧波浩荡，白帆点点，出没天际；斜坡缓舒形
成细软白沙铺底的海滩，水绿沙白，清幽可爱，是附近最佳的天然游泳场每当
盛夏，这里游人如织，柳树丛中，沙滩上，挤满了一群群，一伙伙来消夏的游
人。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
		"north" : __DIR__"hg1",
	]));
        set("objects",([
                "/d/dali/npc/qiaozi" : 1,
        ]));

	set("coor/x",-300);
  set("coor/y",-520);
   set("coor/z",-20);
   setup();
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
       me->set_temp("dali_xc/hg2",1);
      }
}
