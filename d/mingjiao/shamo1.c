// shamo1.c ��ɳĮ
// Modify By River@SJ 99.06
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{ 
       set("short",YEL"��ɳĮ"NOR);
       set("long", @LONG
����һƬһ���޼ʵĴ�ɳĮ����ڡ���һ��������ʧ�˷����ڶ���ʱ��
����һƬƬ�Ļ�ѩ��������һ����Сɳ��
LONG);    
	set("exits", ([
		"west" : __DIR__"shaqiu1",				
                "northeast" : "/d/xingxiu/silk6"
	]));             
        set("outdoors", "˿��֮·");
        set("coor/x",-290);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",-290);
 set("coor/y",90);
   set("coor/z",0);
   setup();
}
