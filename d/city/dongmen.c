// Room: /d/city/dongmen.c

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���Ƕ����ţ��������Ϸ����š����š�����������֣���ǽ�����ż��Ź�
����ʾ(gaoshi)���ٱ��Ǿ����ע���Ź������ˣ������С��Ϊ�һ����ֱ
����ʯ���������������졣�����ǽ��⣬��Լ�ɼ�һƬһ���޼ʵ����֣�
����Ī�⡣�����ǳ��
LONG
	);
        set("outdoors", "����");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"east" : __DIR__"eroad1",
        "south" : "/d/suzhou/yzyunhe",
        "north" : __DIR__"biaoju",
        "northeast" : __DIR__"guandimiao",
		"west" : __DIR__"dongdajie1",
	]));

	set("objects", ([
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
	]));

	set("coor/x",130);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n�Գ�֮\n";
}

