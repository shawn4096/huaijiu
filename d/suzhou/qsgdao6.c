inherit ROOM;

void create()
{
        set("short", "青石官道");
        set("long",@long
你走在一条青石大道上，人来人往非常繁忙，不时地有人骑着马匆匆而过。
大道两旁有一些小货摊，似乎是一处集市。南面就是苏州城了。
long);
set("outdoors", "suzhou");
set("exits",([
"northwest" : "/d/city/sroad1",
"southwest" : __DIR__"huqiushan",
"south" : __DIR__"northgate",
"west" : "/d/gb/tianjing",
]));
set("coor/x",110);
  set("coor/y",-180);
   set("coor/z",0);
   setup();
}
