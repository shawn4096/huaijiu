// Room: /gaibang/xinglin.c
// by pishou

inherit ROOM;

void create()
{
    set("short", "������");
	set("long", @LONG
����һƬ�����֣�һ�߽�������·���ʧ�˷��������ӻ���
�Ҵ�, ��ͼ���ֳ�·��
LONG
	);

	set("exits", ([
		"east" : __FILE__,
        "west" : __DIR__"xinglin4",
        "south" : __DIR__"tianjing",
		"north" : __FILE__,
	]));
	set("coor/x",110);
  set("coor/y",-160);
   set("coor/z",0);
   setup();
}
