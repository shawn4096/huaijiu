// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "����");
	set("long", @LONG
�������������ڵ�һ�����ȣ�����һֱͨ�������ڣ��ȱߵ����˻��ߣ�͸
���ƿյĻ��ƣ���ɿ����������ľ���ݡ���������������������ů��
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
             "north" : __DIR__"lang1",
	     "south" : __DIR__"lang5",
	     "west" : __DIR__"yizhengting",
             "east" : __DIR__"nuange",
        ]));
	 
	set("coor/x",-310);
  set("coor/y",-450);
   set("coor/z",-20);
   setup();
}
