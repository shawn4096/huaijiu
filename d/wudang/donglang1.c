// donglang1.c ��������

#include <ansi.h>
#include <room.h>
inherit ROOM;



void create()
{
        set("short", "��������");
        set("long", @LONG
������һ��ľ�ƽṹ�������ϣ��쾮������������ԣ�����һ��
��������(guoshu)��Ϊ��󡣶����м������ң������䵱���������
ʳ���������������������֡������Ǵ�
LONG
        );

        set("exits", ([
                "east" : __DIR__"donglang2",
                "west" : __DIR__"sanqingdian",
        ]));
        set("item_desc", ([
               "guoshu" : "���������ɽ��ֲ���ɹ����磬��Ϊ���ڷ����ʧȥ������֦Ҷή�ң����ܿ������!\n"
        ]) );

        set("jiao_count", 3);
        set("guo_count", 1);
        
        set("objects", ([
                "/kungfu/class/wudang/xi" : 1]));
                
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("family");

        if ((!myfam || myfam["family_name"] != "�䵱��") && dir == "east" &&
                objectp(present("zhang songxi", environment(me))))
           return notify_fail("����Ϫ�ȵ����䵱�صأ����˲������ڡ�\n");
                
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_jiao", "jiao");
        add_action("do_jiao", "watering");
}

int do_jiao(string arg)
{       mapping fam;
        object me;
        object obguo;
        me = this_player();


        if ( !arg || arg != "guoshu" )
            {    message_vision("$N��ʲô?!\n",me);
                 return 1;
             }
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "�䵱��")
               return notify_fail("���뱾�������������ֺα�����������!\n");

    if ( present("xiang cha", this_player()))

        message_vision(HIG"$Nϸ�ĵذѲ豭���Ů���㽽�ڳ��������ϡ�\n"NOR, me);
        call_out("destroying", 1,me , "xiang cha");
        add("jiao_count", -1);
        if (query("jiao_count") > 0) return notify_fail(HIG"��豻�������գ�֦Ҷ���ø������ˡ�\n"NOR);
           if (query("guo_count") < 1)
              {
               set("jiao_count", 3);
               return notify_fail(HIG"����Ӫ����������������ֻ�ܿ���һ��������С����\n"NOR);
              }
        add("guo_count", -1);
        message_vision(HIM"ͻȻ�����м䳤��һ�����٣��漴���������Ͼͽ��һ�������������εĳ�����! \n"NOR);
        message_vision("$NС�������ժ�³��������������˵ش��뻳�С�\n",me);
        obguo = new(__DIR__"obj/rsg");
        obguo->move(me);
        return 1;
}
void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
