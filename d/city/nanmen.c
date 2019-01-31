// Room: /d/city/nanmen.c

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
�����ϳ��ţ���ǽ�����Źٸ��ĸ�ʾ(gaoshi)���ٱ�����������ؼ��ÿ
һ�����������ˣ��鿴�����Ƿ�Я��˽�Ρ���ʯ�������ϱ��������졣
LONG
	);
        set("outdoors", "����");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"south" : __DIR__"jiangbei",
                "north" : __DIR__"nandajie1",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));

	set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",-50);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n�Գ�֮\n";
}

