#include <wanted.h>
inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
����̩ɽ���ϵ�һ��С·���������������򶫷��ĺ�����·��
����Щ���ݣ���ֻ�����ڻ����з�����ȥ��һ�󺣷紵����ʹ�㾫
�����ˬ�ʡ�
LONG
        );

        set("exits", ([
        "west" : "/d/taishan/daizong",
                "northeast" : __DIR__"haitan",
                
        ]));


        set("outdoors", "taishan");
        set("coor/x",180);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "northeast" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
