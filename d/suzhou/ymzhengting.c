inherit ROOM;

void create()
{
	set("short", "衙门正厅");
	set("long", @LONG
	堂上东西有两根楹住，挂着一幅对联，但是你无心细看。正墙上悬挂一个横
匾，上书“正大光明”四个金光闪闪的大字。知府正坐在文案后批阅文书，师爷随侍
在后。
LONG
	);
        
	set("exits", ([
		"east" : __DIR__"dongting",
		"west" : __DIR__"xiting",
		"north" : __DIR__"neizhai",
		"south" : __DIR__"yamen",
	]));
	set("objects", ([
		__DIR__"npc/zhao" : 1,
		__DIR__"npc/shiye" : 1,
	]));

	set("coor/x",100);
  set("coor/y",-190);
   set("coor/z",0);
   setup();
}

