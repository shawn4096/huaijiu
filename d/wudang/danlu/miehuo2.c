// miehuo2.h Cht@SJ 2000-3-12 修改
#include <ansi.h>
int do_miehuo(string arg)
{
        object me, ob;
        object *inv;
        me = this_object();
        ob = this_player();
        inv = deep_inventory(me);
        if( ob->is_busy())
                return notify_fail("你正忙着呢。\n");
        if( ob->is_fighting())
                return notify_fail("你正在战斗。\n");
        if( !sizeof(inv))
                return notify_fail("炉子里面没有东西。\n");
        if( me->query("marks/open") )
                return notify_fail("炉子正开着呢，瞎灭什么火？\n");
        if( !me->query("marks/doing") && !me->query("marks/fired") )
                return notify_fail("炉子还没点火！\n");
        if( !ob->query_temp("doing", 1) )
                return notify_fail("你没在熬药。\n");
        if( !ob->query_temp("done", 1) )
                return notify_fail("你还没熬完药呢！\n");

        message_vision("\n$N把丹炉内的柴火渐渐地熄灭了。\n", ob);
        remove_call_out("do_drug");
        remove_call_out("do_check");
        remove_call_out("do_ready");
        remove_call_out("do_confirm");
        remove_call_out("do_failed");
        if( random(300)>(int)ob->query_skill("liandan-shu",1) ) {
                call_out("do_drug3",1,me);
                me->delete("marks/aoyao");
                me->delete("marks/burned");
                me->delete("marks/doing");
                ob->start_busy(5);
                message_vision(HIR"\n糟糕！由于$N的炼丹技艺不精，药方操作发生错误了。\n"NOR,ob);
                return 1;
        }
        call_out("do_drug", 1 , me);
        me->delete("marks/aoyao");
        me->delete("marks/burned");
        me->delete("marks/doing");
        ob->start_busy(5);
        return 1;

}

void do_drug()
{
        int a, b, c, i, z;
        object obj, *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        a = 0;
        b = 0;
        c = 0;
        i = 0;
        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        if( inv[i]->name() == HIW"菊梗"NOR)
                        {
                                a = a+1;
                         }
                        if( inv[i]->name() == HIC"木瓜"NOR)
                        {
                                b = b+1;
                         }
                        if( inv[i]->name() == HIG"神农草"NOR)
                        {
                                c = c+1;
                         }
                         if( (int)ob->query_temp("done", 1) == 1)
                         {
                                z = 1;
                         }
                }

// 茯苓忘忧散
                if(  sizeof(inv) != 3
                ||  a != 1
                ||  b != 1
                ||  c != 1
                ||  z != 1)
                {
                 remove_call_out("do_drug1");
                 call_out("do_drug1", 0, me);
                }

                else
                {
                        for(i=0; i<sizeof(inv); i++)
                        {      destruct(inv[i]);   }
                obj=new("/clone/medicine/wangyou-san");
                obj->move(ob);
                message_vision(YEL"\n$N小心翼翼地从丹炉中取出一份茯苓忘忧散。\n"NOR, ob);
                remove_call_out("do_over");
                call_out("do_over", 0, obj);
                }
        }
        return;
}

void do_drug1()
{
        int a, b, c, i, z;
        object obj, *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        a = 0;
        b = 0;
        c = 0;
        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        
                        if( inv[i]->name() == HIC"木瓜"NOR)
                        {
                                a = a+1;
                         }
                        if( inv[i]->name() == GRN"何首乌"NOR)
                        {
                                b = b+1;
                         }
                        if( inv[i]->name() == HIG"神农草"NOR)
                        {
                                c = c+1;
                         }
                         if( (int)ob->query_temp("done", 1) == 1)
                         {
                                z = 1;
                         }
                }

// 天心解毒丹
                if(  sizeof(inv) != 3
                ||  a != 1
                ||  b != 1
                ||  c != 1
                ||  z != 1)
                {
                 remove_call_out("do_drug2");
                 call_out("do_drug2", 0, me);
                }
                else
                {
                        for(i=0; i<sizeof(inv); i++)
                        {      destruct(inv[i]);   }
                obj=new("/clone/medicine/jiedu-dan");
                obj->move(ob);
                message_vision(YEL"\n$N小心翼翼地从丹炉中取出一颗天心解毒丹。\n"NOR, ob);                                                                 
                remove_call_out("do_over");
                call_out("do_over", 0, obj);
                }
        }
        return;
}

void do_drug2()
{
        int a, b, c, i, z;
        object obj, *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        a = 0;
        b = 0;
        c = 0;
        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        
            if( inv[i]->name() == GRN"何首乌"NOR)
                        {
                                a = a+1;
                         }
            if( inv[i]->name() == HIR"小红花"NOR)
                        {
                                b = b+1;
                         }
            if( inv[i]->name() == HIG"神农草"NOR)
                        {
                                c = c+1;
                         }

            if( (int)ob->query_temp("done", 1) == 1)
                         {
                                z = 1;
                         }
                }

// 白虎夺命丸
                if(  sizeof(inv) != 3
                ||  a != 1
                ||  b != 1
                ||  c != 1
                ||  z != 1)
                {
                 remove_call_out("do_drug3");
                 call_out("do_drug3", 0, me);
                }
                else
                {
                        for(i=0; i<sizeof(inv); i++)
                        {      destruct(inv[i]);   }
                obj=new("/clone/medicine/duoming-wan");
                obj->move(ob);
                message_vision(YEL"\n$N小心翼翼地从丹炉中取出一颗白虎夺命丸。\n"NOR, ob);        
                remove_call_out("do_over");
                call_out("do_over", 0, obj);
                }
        }
        return;
}

void do_drug3()
{
        int i;
        object *inv;
        object me = this_object();
        object ob = this_player();
        inv = deep_inventory(me);

        if( sizeof(inv))
        {
                for(i=0; i<sizeof(inv); i++)
                {
                        destruct(inv[i]);
                }
                message_vision(HIR"\n由于药方错误，$N炼丹失败了。\n"NOR,ob);
                ob->delete_temp("doing");
                ob->delete_temp("done");
                message_vision(BLU"\n道童们七手八脚的从铜鼎中铲出一些烧的焦黑的药物残渣，再注入清水清洗，\n"+
                               "$N一声不吭，羞愧地退了下来。\n"NOR, ob);
                if( userp(ob) ) log_file("LIAN_DAN",
                sprintf("%s %s(%s) 因为药方错误炼丹失败 于 %s\n", ob->query("title"), ob->name(1), geteuid(ob), ctime(time())[4..19] ) );
                me->delete("marks/fired");
                me->delete("liquid/remaining");
                me->delete("liquid/name");
        }
        return;
}

void do_over(object obj)
{       
        object me = this_object();
        object ob = this_player();

        ob->delete_temp("doing");
        ob->delete_temp("done");
        me->delete("marks/fired");
        me->delete("liquid/remaining");
        me->delete("liquid/name");   

        if( userp(ob) ) log_file("LIAN_DAN",
        sprintf("%s %s(%s)炼制%s(%s) 于 %s\n", ob->query("title"), ob->name(1), geteuid(ob), obj->name(1), obj->query("id"), ctime(time())[4..19] ) );

        return;
}
