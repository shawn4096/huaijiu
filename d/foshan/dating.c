// Room: dating.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "凤府大厅");
	set("long", @LONG
这里便是凤府的大厅，气派非凡，装饰奢华，居中一张太师椅，上铺
一张黄章黑纹的虎皮，凤天南正坐在太师椅上，正侧身和身旁的师爷嘀咕
着。虎皮椅旁边有两座大理石屏风，都有三四尺高，石上山水木石，便如
是画出来的一般。
LONG
	);
	set("no_clean_up", 0);
	set("exits", ([ /* sizeof() == 2 */
            "west" : __DIR__"dayuan",
            "south" : __DIR__"shufang",
]));

        set("objects", ([
            __DIR__"npc/dashou" : 2,
            __DIR__"npc/he" : 1,
]));

	set("coor/x",30);
  set("coor/y",-550);
   set("coor/z",0);
   setup();
}
