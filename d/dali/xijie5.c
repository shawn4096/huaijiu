// Room: /dali/xijie2.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
        set("short", "���������");
	set("long", @LONG
��������ڱ��ߵ�����ó�нֺͶ����ߵĳ����ģ��Եð����˺öࡣ����
������������ս�£�һƬ̫ƽʢ����ģ�������߹�ȥ�����Ʋ������̩�ĸ�ۡ
�ˣ������Ǵ������֣��������̫�����֡�
LONG
	);
        set("outdoors", "����");
	set("exits", ([ /* sizeof() == 2 */
        "south" : __DIR__"xijie6",
        "north" : __DIR__"xijie4",
        "west" : __DIR__"shanhou",
]));
	set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-430);
   set("coor/z",-20);
   setup();
}
