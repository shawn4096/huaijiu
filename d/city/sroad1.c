inherit ROOM;

void create()
{
        set("short", "青石官道");
        set("long",@long
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
北面是长江下游近入海口的地方，东南面通往姑苏城。
long);
	set("outdoors", "suzhou");
	set("exits",([
        "southeast" : "/d/suzhou/qsgdao6",
		"north" : __DIR__"jiangnan",
	]));
	set("coor/x",100);
  set("coor/y",-170);
   set("coor/z",0);
   setup();
}
