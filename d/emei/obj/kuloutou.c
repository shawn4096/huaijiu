// kuloutou.c 骷髅头
// Last modify by Yanyang because erroneous word

inherit ITEM;

void create()
{
        set_name("骷髅头", ({ "kulou tou", "kulou", "tou" }) );
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("value", 20);
                set("long", "这是一个人头枯烂后形成的骷髅头，上面有五个指洞，看起来阴森森的。\n");
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
if(!arg) return 0;
if (arg!="kulou" && arg!="kulou tou" && arg!="骷髅头" && arg!="骷髅" && arg!="tou")
        return 0;
    if( me->is_fighting() || me->is_busy() )
        return notify_fail("你正忙着呢。\n");
    if( me->query_skill("claw", 1) > 100)
             return notify_fail("你发现再怎么插也没有用了。\n");
if( (int)me->query_skill("claw",1) >= 180 && me->query("potential")>0 ){
        me->add("jing", -(20 + random(40)));
        me->add("jingli", - random(40));
        me->add("shen", -random(180));
        message_vision("$N把五个手指插入骷髅头上的五个指孔。\n", me);
        tell_object(me, "你忽然觉得五个手指正好插进了指孔，心里不由自主地产生一股邪念。\n");
        me->improve_skill("claw", random((int)me->query_int())+(int)me->query_skill("claw"));
 me->add("potential",-2-random(2));
if( !(me->query("potential")>0)) 
me->set("potential",0);
        if( !random(30) ) 
            call_out("destroying", 1, this_object(), me);
        return 1;
    }
    if( (int)me->query_skill("claw",1) >= 50 ) {
        message_vision("$N看着骷髅头上的五个指孔，发呆沉思。\n", me);
        tell_object(me, "你忽然觉得自己似乎不应该这么邪恶。\n");
        return 1;
    }
    me->add("jing", -(20 + random(40)));
    me->add("jingli", - random(40));
    me->add("shen", -random(80));
    me->improve_skill("claw", (int)me->query_int()+random((int)me->query_skill("claw")));
    message_vision("$N把五个手指插入骷髅头上的五个指孔。\n", me);
    tell_object(me, "你忽然觉得五个手指正好插进了指孔，好像被什么咬了一下，吓了一大跳。\n");
    return 1;
}

void destroying(object obj, object me)
{     
    tell_object(me, "你五个手指狠狠叫劲，整个骷髅头都被你捏碎了。\n");
    message_vision("$N五指叫劲，只听得一声脆响，整个骷髅头都被$N捏碎得粉碎。\n", me);
    destruct(obj);
    return;
}     
