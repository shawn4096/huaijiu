// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺ��뺣��");
	set("long", @LONG
�ƺ�������ظ�ԭ��������ԭ������ƽԭ���ܳ�һ����Ű��
���������󺣡�
LONG );
	set("exits", ([
		"southwest" : __DIR__"huanghe7",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",190);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}

