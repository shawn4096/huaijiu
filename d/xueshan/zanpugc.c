// Room: zanpugc.c

inherit ROOM;

void create()
{
	set("short", "���չ㳡");
	set("long", @LONG
�����ǻʳ����ĵ�һƬ�㳡���㳡����������ެ���յ�ʯ��������������
�����в����������𾢵�ߺ���š��㳡���������ڽ����е���ެ�»ʹ���һ�Ӷ�
���������װ��ʯ��ľ�ϵ��Ƴ��߹�ȥ��������ެ��ʿ������·�ڣ������ע��
���������������ˡ������Ƿ����ţ���ͨ����ެ�������´����µıϾ�֮·��
LONG
	);

	set("exits", ([
		"west" : __DIR__"fozhaomen",
		"east" : __DIR__"huanggong",
		"north" : __DIR__"jiedao3",
		"south" : __DIR__"jiedao2",
	]));
        set("objects", ([__DIR__"npc/tufanwushi" : 3,]));
        set("outdoors", "ѩɽ");
	set("coor/x",-220);
  set("coor/y",120);
   set("coor/z",0);
   setup();

}
