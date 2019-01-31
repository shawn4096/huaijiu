void check_skills(object ob)
{       
        mapping skl;
        object  me;
        string *sname;
        int i, counter, ob_shen, ob_exp;
        me = this_object();
        skl = ob->query_skills();
        sname  = sort_array( keys(skl), (: strcmp :) );
        ob_shen = (int)ob->query("shen");
        ob_exp = (int)ob->query("combat_exp");
        counter = 0;
        for(i=0; i<sizeof(skl); i++){
                if (skl[sname[i]] >= 100)
                        counter++;
                }
        if( !random(10) && counter >= 3 && ob_exp > 100000 ){
                me->set_leader(ob);
                if ( !environment(me)->query("no_fight")) do_kill(me, ob);
                else waiting(me, ob);
                }
}
int do_kill(object me, object dest)
{
	remove_call_out("do_kill");
        if( objectp(dest) && present(dest, environment(me))
                 && !environment(me)->query("no_fight")){
                message_vision(HIR "$N��$n����һЦ�������ŵķ��⣬"+RANK_D->query_rude(dest)+"�����ү�������ɣ�\n" NOR, me, dest);
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);
                checking(me, dest);
                }        
        else call_out("waiting", 2, me, dest);
        return 1;
}

int waiting(object me, object dest)
{
	remove_call_out("waiting");
    if ( objectp(dest) ){
        if (dest->is_ghost()){
                call_out("do_back", 5+random(5), me);
                return 1;
                }
        else if (me->is_fighting() && present(dest, environment(me))){
                call_out("checking", 1, me, dest);
                return 1;
                }
        else if (living(me) && environment(dest)->query("no_fight")){
                call_out("do_back", 2, me);
                return 1;
                }
        }
        call_out("waiting", 1, me, dest);
        return 1;
}

int checking(object me, object dest)
{
        object ob;

	remove_call_out("checking");
        if(!dest) return 0;
        if(!present(dest, environment(me))) call_out("waiting", 2, me, dest);
        if(!me->is_fight(dest)) me->kill_ob(dest);
        if (me->is_fighting()){
           call_out("checking", 1, me, dest);
           return 1;
           }
        if( objectp(ob = present("corpse", environment(me)))
          && ob->query("victim_name") == dest->query("name") ){
           command("chat* kick corpse");
           tell_room(environment(me), me->query("name")+"���������ϵĻҳ����첽���˳�ȥ��\n" NOR, ({me}));
           call_out("do_back", 2, me);
           return 1;
           }
        call_out("waiting", 1, me, dest);
        return 1;
}
