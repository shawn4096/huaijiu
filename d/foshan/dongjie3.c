// Room: /d/fuoshan/dongjie3.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "��ɽ����");
	set("long", @LONG
�����ڽ��ϣ�����ϡ��������������һ�¸�ǽ��ǽ��д��һ�����
�ġ������֣���ϸ��������������ѹ�͵��ּۻ��۵������������Ƿ�ɽ��
�ţ�ͨ����⡣
LONG
	);
        set("outdoors","��ɽ");
	set("exits", ([
  "south" : __DIR__"dangpu",
  "east" : __DIR__"dongmen",
  "west" : __DIR__"dongjie2",
]));
	set("no_clean_up", 0);

	set("coor/x",30);
  set("coor/y",-530);
   set("coor/z",0);
   setup();

}
