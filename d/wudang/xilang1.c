// xilang.c ��������
// by shang 97/6

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
������һ�������ϣ��ϱ���һ��¥����������һ��������, ������һС����
������䵱����, �ǳ�����, ��һ�䵱���ӿ����š�
LONG
        );

        set("exits", ([
                "southup" : __DIR__"cangjingge",
                "east" : __DIR__"xiaolu1",
                "west" : __DIR__"liandanfang",
                "northwest" : __DIR__"xiaolu7",

        ]));

        set("objects", ([
                "/kungfu/class/wudang/xi" : 1]));

   setup();
} 
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

        if ((!myfam || myfam["family_name"] != "�䵱��") && dir != "east" &&
                objectp(present("zhang songxi", environment(me))))
           return notify_fail("����Ϫ�ȵ����䵱�صأ����˲������ڡ�\n");
                
        return ::valid_leave(me, dir);
}
