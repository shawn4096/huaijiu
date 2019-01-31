// Room: /city/ximen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���������ţ�����ǰ�����⵽���˵Ĺ�������Ե���Щ�ưܡ�������
�Ϸ�����ǿǿ�����ϳ������š��������֣���ǽ�����ż���ͨ����ʾ(gaoshi)��
�������ﷸ��������ıؾ�֮�أ��ٱ��ǽ䱸ɭ�ϣ��������ͽ�ס�������ʡ�
һ����ֱ����ʯ���������������졣�����ǽ��⣬����ġ����εġ���
·�ģ����˴Ҵҡ���ӿ��˽Ų������¹ٱ��Ҳꡣ�����ǳ��
LONG
	);
        set("outdoors", "suzhou");

	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits",([
                 "west" : __DIR__"qsgdao3",
                 "east" : __DIR__"xidajie2",
        ]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
	set("coor/x",80);
  set("coor/y",-210);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��֪��\n";
}

