// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "μ������");
	set("long", @LONG
�ںӺ�μ�ӻ���ƺӣ���������ˮ�ƣ�Ҳ�����˸������ɳ������
�Ӷ��ǽ����������¡�
LONG );
	set("exits", ([
		"south" : __DIR__"huanghe1",
		"north" : __DIR__"huanghe_1",
                "southwest" : "/d/shaolin/yidao4",
	]));
	set("no_clean_up", 0);
	set("outdoors", "�ƺ�");
	set("coor/x",120);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

