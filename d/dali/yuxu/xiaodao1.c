// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "������Ұ");
	set("long", @LONG
�����������Ұ���ϣ����������԰��⣬�㲻����������һ���������
������Ŀ�����
LONG
	);
        set("outdoors", "����");
	set("exits", ([ /* sizeof() == 1 */
	    "west" : __DIR__"xiaodao2",
	    "northeast" : "/d/dali/dadao1",
        ]));
	set("no_clean_up", 0);

	set("coor/x",-50);
  set("coor/y",-60);
   set("coor/z",0);
   setup();
}
