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
        "east" : __DIR__"xinglin6",
		"west" : __FILE__,
        "south" : __DIR__"tianjing",
		"north" : __FILE__,
	]));
	set("coor/x",100);
  set("coor/y",-150);
   set("coor/z",0);
   setup();
}
