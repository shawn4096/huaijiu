// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "�������");
	set("long", @LONG
�ߵ����������ǻ�ǽԭ�������¹ۣ��Ҷ���д���ƺ��ǡ�����ۡ����֣�
��ǽ���ߣ���ۿ��������Ǽ�ª���ſ�վ������С��ͯ���
LONG
	);
        set("outdoors", "����");
	set("exits", ([ /* sizeof() == 1 */
	    "enter" : __DIR__"yuxuguan",
	    "east" : __DIR__"dadao5",
        ]));
        set("objects", ([
	__DIR__"npc/daotong" : 2 ]) );

	set("no_clean_up", 0);

	set("coor/x",-90);
  set("coor/y",-50);
   set("coor/z",0);
   setup();
}
