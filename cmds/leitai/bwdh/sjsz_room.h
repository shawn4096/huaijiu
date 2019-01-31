// sjsz_room.h 

void reset()
{
	::reset();
	set("dig_times", 10 + random(20));
}

void init()
{
        object me;
        me = this_player();
        if (!me->query_condition("sjsz_time") && userp(me)){
           tell_object(me,BLINK + HIC"突然从边上窜出两个彪形大汉，一把抗起你，丢到了城隍庙。你顿时郁闷了半天。\n"NOR);
           me->move("/d/city/chmiao");
           me->clear_condition("killer");
           me->remove_all_enemy();
           me->remove_all_killer();
           if (me->query("no_pk_recover")){
               tell_object(me,BLINK + HIG"您离开了试剑山庄，系统自动恢复了您的洗手状态！\n"NOR);
               me->set("no_pk",me->query("no_pk_recover"));
               me->delete("no_pk_recover");
           }
       }
}