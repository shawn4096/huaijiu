// By River 98/12/
inherit ROOM;

void create()
{
        set("short", "定安府");
	set("long", @LONG
这是大理的司法机关，接管的主要是一些民族之间的纠纷和误解，因此府
里有汉族，白族，摆夷族，哈尼族，壮族官员各一名，以示公正。另外，府里
还雇了通译，以便讯问。近年来事态安和，定安府门前清清淡淡。
LONG
	);
	set("exits",([ 
             "north" : __DIR__"nanjie2",
        ]));

        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));
    
	set("coor/x",-320);
  set("coor/y",-470);
   set("coor/z",-20);
   setup();
}
