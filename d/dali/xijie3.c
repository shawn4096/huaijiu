// Room: /dali/xijie2.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
        set("short", "���������");
	set("long", @LONG
���Ǵ�������֣�������հ���������½֣��ֽй����֡��ǰ�������ó
�йŽ֡�ÿ�����£����Ｗ���˽��׵���Ⱥ�����������¿��ĳ��ׯ�������
������ʱ�п��������˴����������̫�������ˡ�
LONG
	);
        set("outdoors", "����");
	set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"xijie2",
        "south" : __DIR__"xijie4",
        "west" : __DIR__"chouduan",
        ]));
	set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-410);
   set("coor/z",-20);
   setup();
}
