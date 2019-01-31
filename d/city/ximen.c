// Room: /d/city/ximen.c

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���������ţ���ǽ�����ż���ͨ����ʾ(gaoshi)��������������ıؾ�֮
�أ��ٱ��ǽ䱸ɭ�ϡ�һ����ֱ����ʯ���������������졣�����ǽ��⣬
����ġ����εġ���·�ģ����˴Ҵҡ������ǳ��������֡�
LONG
	);
	set("outdoors", "����");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"east" : __DIR__"xidajie1",
		"west" : __DIR__"wroad1",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
	set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",70);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n�Գ�֮\n";
}

