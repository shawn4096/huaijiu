// kuloutou.c 骷髅头

inherit ITEM;

void create()
{
        set_name("骷髅头", ({ "kulou tou" }) );
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("value", 30);
                set("long", "这是一颗骷髅头，上面有五个指洞，你不禁想将手指插入(insert)进去。\n");
                set("no_cun", 1);
                set("no_give", 1);
		set("no_get", "这样东西不能离开那儿。\n");
		set("treasure",1);
                set("degree",1);
                set("no_drop", 1);
                set("credit",50);
                set("desc","消除一次九阴下解密失败记录的辅助物品。");
               
        }
        setup();
}

void init()
{
    add_action("do_cha",({"cha","insert"}));
}

int do_cha(string arg)
{
    object me=this_player();

    if( !arg ) return 0;

    if( arg!="kulou tou" && arg!="骷髅头" ) return 0;
       
    if( me->is_fighting() || me->is_busy() )
            return notify_fail("你正忙着呢。\n");

    if( !me->query("jiuyin/chenfail") )
            return notify_fail("你之前有过失败记录吗？\n");

    message_vision("$N把五个手指插入骷髅头上的五个指孔。\n", me);

    tell_object(me, "你忽然觉得五个手指正好插进了指孔，心里不由自主地产生一股邪念。\n");

    me->add("jiuyin/chenfail", -1);
            
    tell_object(me, "你五个手指狠狠叫劲，整个骷髅头都被你捏碎了。\n");
    
    message_vision("$N五指叫劲，只听得一声脆响，整个骷髅头都被$N捏碎得粉碎。\n", me);

    destruct(this_object());

    return 1;
    }
