// donglang1.c 东厢走廊

#include <ansi.h>
#include <room.h>
inherit ROOM;



void create()
{
        set("short", "东厢走廊");
        set("long", @LONG
你走在一条木制结构的走廊上，天井里种有许多盆栽，其中一株
长生果树(guoshu)就为珍贵。东边有几间雅室，那是武当弟子起居饮
食场所。人来人往很是热闹。西边是大殿。
LONG
        );

        set("exits", ([
                "east" : __DIR__"donglang2",
                "west" : __DIR__"sanqingdian",
        ]));
        set("item_desc", ([
               "guoshu" : "这是株从深山移植的仙果树苗，因为长于凡间而失去灵气。枝叶萎靡，不能开花结果!\n"
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

        if ((!myfam || myfam["family_name"] != "武当派") && dir == "east" &&
                objectp(present("zhang songxi", environment(me))))
           return notify_fail("张松溪喝道：武当重地，外人不得入内。\n");
                
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
            {    message_vision("$N浇什么?!\n",me);
                 return 1;
             }
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "武当派")
               return notify_fail("你与本派素无来往，又何必武事献殷勤!\n");

    if ( present("xiang cha", this_player()))

        message_vision(HIG"$N细心地把茶杯里的女儿香浇在长生果树上。\n"NOR, me);
        call_out("destroying", 1,me , "xiang cha");
        add("jiao_count", -1);
        if (query("jiao_count") > 0) return notify_fail(HIG"香茶被果树吸收，枝叶长得更翠绿了。\n"NOR);
           if (query("guo_count") < 1)
              {
               set("jiao_count", 3);
               return notify_fail(HIG"由于营养不良，长生果树只能开出一朵美丽的小花。\n"NOR);
              }
        add("guo_count", -1);
        message_vision(HIM"突然果树中间长出一个花蕾，随即开花，马上就结成一个令人唾咽欲滴的长生果! \n"NOR);
        message_vision("$N小心翼翼地摘下长生果，满脸高兴地揣入怀中。\n",me);
        obguo = new(__DIR__"obj/rsg");
        obguo->move(me);
        return 1;
}
void destroying(object me, object obj)
{
        destruct(obj);
        return;
}
