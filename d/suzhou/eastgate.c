// Room: /city/dongmen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���Ƕ����ţ��������Ϸ����š����š�����������֣���ǽ�����ż���
�ٸ���ʾ(gaoshi)���ٱ��Ǿ����ע���Ź������ˣ������С��Ϊ�һ��
��ֱ����ʯ���������������죬�����ǳ��
LONG
	);
        set("outdoors", "suzhou");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
	//	"east" : "",
        //	"north" : __DIR__"ml1",
		"west" : __DIR__"dongdajie2",
	]));

	set("objects", ([
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
	]));

	set("coor/x",160);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��֪��\n";
}

