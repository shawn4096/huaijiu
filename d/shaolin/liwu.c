//liwu

#include <ansi.h>
 
inherit ROOM;

void create()
{
      set("short", HIW"����"NOR);
    set("long",@LONG
���ݵĳ���͸��Ӽ򵥣�һ�ѷ�����һ�����棬�������һ����ɮ����
��Ŀ�붨��
LONG
    );
    set("exits",([
         "out"  :    __DIR__"houyuan",
        
    ]));
	set("objects",([
                "/kungfu/class/shaolin/wumingseng" : 1,
	]));
       	set("valid_startroom", 1);
	set("no_clean_up", 0);
    	setup();
}
 
