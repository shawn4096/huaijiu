// zhushao
// 98.8.5  by emnil

#include <ansi.h>

inherit ITEM;

//void uncon(object me,int time);
void hs(object me,int time);

void create()
{
        set_name(HIG"����"NOR, ({ "zhushao","shao" }) );
        set("long",HIG"����һֻ����ѱ�ߵ����ڡ�\n"NOR);
        set("unit", "ֻ");
        set("weight", 50);
        set("no_sell",1);
        set("no_get",1);
        set("no_steal",1);
        set("no_drop",1);
        set("no_give",1);
        set("value", 1);
} 

void init()
{
        add_action("do_xunshe","xunshe");
        add_action("do_zhaoshe","zhaoshe");
        add_action("do_fangshe","fangshe");
        add_action("do_nashe","nashe");
        add_action("do_chushe","chushe");
//	add_action("do_she","she");
        add_action("do_wield","wieldshe");
        add_action("do_unwield","unwieldshe");
      add_action("do_du","pengdu");
//      add_action("do_hs","hushen");
//      add_action("do_pfm","perform");
}
/*
int do_pfm(string arg)
{
        object me=this_player();

        if(me->query_temp("hushen",1))
                return 1;
        return 0;        
}

int do_hs(string arg)
{
        object me=this_player();
        int fskill,nl,times;

        fskill=me->query_skill("dulong-dafa",1);
        nl=me->query("neili");
        if(fskill < 100 || nl < 1000)
                return 0;
        message_vision(HIY"$NͻȻ��һ������ȫ���ɫɲ�Ǽ���"RED"Ѫ��ɫ��\n"NOR,me);
        times=fskill/3;
        me->set_temp("hushen",1);
        me->add("neili",-1000);
        if(random(10)!=0)
         me->add("max_neili",-1);
        call_out("hs", 0,me,times);
        return 1;
}

void hs(object me,int time)
{ 
        int eqi,mqi,ejing,mjing;

        if(objectp(me) && !me->is_ghost())
        {
                eqi=me->query("eff_qi");
                mqi=me->query("max_qi");
                //mqi-=eqi;
                ejing=me->query("eff_jing");
                mjing=me->query("max_jing");
                //mjing-=ejing;
                if(eqi*2<mqi)
                        me->set("eff_qi",mqi/2);
                me->set("qi",me->query("eff_qi"));
                if(ejing*2<mjing)
                        me->set("eff_jing",mjing/2);
                me->set("jing",me->query("eff_jing"));
                me->add("jingli",-50);
                me->add("neili",-100);
                //me->set("neili",0);
                if(me->is_fighting() && time>0)
                {
                        remove_call_out("hs");
                        call_out("hs", 0,me,time-1); 
                }
                else
                        me->delete_temp("hushen");
        }
        else if(objectp(me))
                me->delete_temp("hushen");                              
}

*/
int do_du(string arg)
{
        object me=this_player();
        object * en;
        int pskill,fskill,nl,i,dis,busytime;

        en=all_inventory(environment(me));
        pskill=me->query_skill("poison",1);
        fskill=me->query_skill("dulong-dafa",1);
        nl=me->query("neili");
        if(pskill<100 || fskill < 100 || nl < 1000)
                return 0;
        message_vision(HIY"$N��Ȼ��һ�ţ���ȫ��֮�������һ��"RED"��"GRN"��"YEL"��"WHT"ɫ"HIY"֮����\n"NOR,me);
        busytime=fskill/50+pskill/100;
        if(busytime<=me->query_busy()) 
                busytime=me->query_busy()+5;
        for(i;i<sizeof(en);i++)
        {
                if(!living(en[i]) || wizardp(en[i]) || en[i]==me)
                        continue;
                dis=(int)en[i]->query_skill("dodge",1);
                dis=dis*en[i]->query_kar()*en[i]->query_dex()/1000;
                if(random(dis)>200)
                {
                        tell_room(environment(en[i]),en[i]->name(1)+"һ�������һ�ߡ�\n");
                        continue;
                }
                tell_object(en[i],"�㱻����һѬ���е����е������ء�\n");
                en[i]->start_busy(busytime);
        }
        me->set("neili",0);
        me->add("max_neili",-1);
        me->set("qi",0);
        me->set("jing",0);
        me->set("jingli",me->query("eff_jingli"));
        tell_object(me,"��ȫ������������������һ����\n");
        call_out("uncon", 1,me,busytime);
        return 1; 
}

void uncon(object me,int time)
{
        if(objectp(me) && !me->is_ghost())
        {
                if(time>0)
                {
                        me->set("neili",0);
                        me->set("qi",0);
                        me->set("jing",0);
                        //me->set("jingli",me->query("jingli")/10+1);
                        call_out("uncon", 1,me,time-1);
                }
        }
}

int do_xunshe(string arg)       
{
        object me;

        me=this_player();
        if((int)me->query_skill("dulong-dafa",1) < 100) 
                return notify_fail("��Ķ�������Ϊ����������ѱ�ߡ�\n");
        if((int)me->query_temp("haveownsnake", 1) == 1)
                return notify_fail("���Ѿ���һ�����ˡ�\n");
        if((int)environment(me)->query("canfindsnake")!=1)
                return notify_fail("���������Ҳ����ߡ�\n");

        message_vision(HIG"$N�ó����ڣ����ĵĴ�����������һ�����һ�����������С�ߴ����������˳�����\n"+
                          "$N����ָ�쵽����ǰ��С������$N�ľ�Ѫ��$N������ͻȻ�ֳ�һ˿��⣡\n"NOR,me);
        me->add("max_jingli",-1);
        me->add("eff_jingli",-1);
        me->set_temp("haveownsnake",1);
        me->set_temp("havegetsnake",0);
        me->set_temp("mysnake",0);
        return 1;
}

int do_zhaoshe(string arg)      
{ 
        object me,ob;
        int skill,exp,i;

        me=this_player();
        if((int)me->query_temp("haveownsnake",1)!=1)
                return notify_fail("�㻹û���ߡ�\n");
        if(((int)me->query_temp("havegetsnake",1)==1) && 
           objectp(me->query_temp("mysnake",1)))
                return notify_fail("���Ѿ��õ����ˡ�\n");
        if((int)environment(me)->query("canfindsnake")!=1)
                return notify_fail("���������Ҳ����ߡ�\n");

        message_vision(HIG"$N�ó����ڣ����ĵĴ�����������һ�����һ�����������С�ߴ���$N�����ϡ�\n"NOR,me);

        seteuid(getuid());

        ob = new(__DIR__"ssnake");
        if (!ob)  return notify_fail("�쳣����\n");
        ob->set("owner",me);
        skill=(int)me->query_skill("dulong-dafa",1);
        exp= me->query("combat_exp")/200 * skill; 
        if( exp > 100000)
          ob->set("combat_exp",exp);
        else
          exp = 100000;
        ob->set("max_qi",me->query("max_qi"));
        ob->set("eff_qi",me->query("eff_qi"));
        ob->set("qi",me->query("qi"));  
        ob->set("max_jing",me->query("max_jing"));
        ob->set("eff_jing",me->query("eff_jing"));
        ob->set("jing",me->query("jing")); 
        ob->set("neili",me->query("max_neili"));
        ob->set("max_neili",me->query("max_neili"));
        ob->set("jingli",me->query("jingli"));
        ob->set("eff_jingli",me->query("eff_jingli"));
        i = random(exp/5000);
        if ( i > 150) i = 150;
        if ( i < 2) i = 2;
        ob->set_temp("apply/attack",i);
        ob->set_temp("apply/defense",i*15/10);
        ob->set_temp("apply/damage",i);
        ob->set_temp("apply/armor", i /2);
   
        ob->move(me);

        me->set_temp("havegetsnake",1);
        if(objectp(me->query_temp("mysnake",1))) 
          destruct(me->query_temp("mysnake",1));
        me->set_temp("mysnake",ob);
        ob->snakehd();
        return 1;
}

int do_fangshe(string arg)      
{
        object me;
        object * all;
        int i,j;

        me=this_player();
        if((int)me->query_temp("haveownsnake",1)!=1)
                return notify_fail("�㻹û���ߡ�\n");
        if((int)me->query_temp("havegetsnake",1)!=1)
                return notify_fail("��û���õ��ߡ�\n");
        if((int)environment(me)->query("canfindsnake")!=1)
                return notify_fail("�㲻����������ߡ�\n");
        if(me->query_temp("wieldsnake",1)!=0)
                    return notify_fail("�������װ���š�\n");
        all = all_inventory(me);                      
        j=0; 
        for (i=0; i<sizeof(all); i++)   {
                if ( all[i] == me->query_temp("mysnake",1) ) j=1;
        }
        if (j==0)  return notify_fail("��������ڲ��������ϣ�\n");

        message_vision(HIG"$N����İ�С�߷��£���������ͷ��С�����һ���ʹܻ�������ȥ�ˡ�\n"NOR,me);

        destruct(me->query_temp("mysnake",1));
        me->set_temp("havegetsnake",0);
        me->set_temp("mysnake",0);

        return 1;
}

int do_nashe(string arg)        
{
        object * all,me;
        int i , j;

        me=this_player();
        if((int)me->query_temp("havegetsnake",1)!=1)
                return notify_fail("��û���õ��ߡ�\n");
 
        all = all_inventory(environment(me));                      
        j=0;
        for (i=0; i<sizeof(all); i++)   {
                if ( all[i] == me->query_temp("mysnake",1) ) j=1;
        }
        if (j==0)  return notify_fail("��Ҫ�õ��߲�������ѽ��\n");

        message_vision("$N��������С�ߡ�\n",me);
        (me->query_temp("mysnake",1))->move(me);

        return 1;
}

int do_chushe(string arg)       
{
        object * all,me;
        int i , j;

        me=this_player();
        if((int)me->query_temp("havegetsnake",1)!=1)
                return notify_fail("��û���õ��ߡ�\n");
        if(me->query_temp("wieldsnake",1)!=0)
                    return notify_fail("�������װ���š�\n"); 

        all = all_inventory(me);                      
        j=0;
        for (i=0; i<sizeof(all); i++)   {
                if ( all[i] == me->query_temp("mysnake",1) ) j=1;
        }
        if (j==0)  return notify_fail("������Ѿ��ų�ȥ�ˣ�\n");

        message_vision("$N�������С�ߡ�\n",me);
        (me->query_temp("mysnake",1))->move(environment(me));

        return 1;
}

int do_she(string arg)  
{
        object * all,me,ob;
        int i , j;

        me=this_player();
        if((int)me->query_temp("havegetsnake",1)!=1)
                return notify_fail("��û���õ��ߡ�\n");
        if(!objectp(ob=me->query_temp("mysnake",1)))
                return notify_fail("������û���ߡ�\n");
        all = all_inventory(me);
        j=0;
        for (i=0; i<sizeof(all); i++)   {
                if ( all[i] == ob ) j=1;
        }
        if (j==1)  return notify_fail("����߻�û�зų�ȥ��\n");
//      ob->command(arg);
        ob->do_command(arg);
        return 1;
}

int do_wield(string arg)
{
        object me,weapon;
        object * all;
        int i,j,exp,damage;

        me=this_player();
        if(me->query_temp("wieldsnake",1)!=0) 
                    return notify_fail("������Ѿ�װ���š�\n");
        if((int)me->query_temp("haveownsnake",1)!=1)
                return notify_fail("�㻹û���ߡ�\n");
        if((int)me->query_temp("havegetsnake",1)!=1)
                return notify_fail("��û���õ��ߡ�\n");

        all = all_inventory(me);                      
        j=0;
        for (i=0; i<sizeof(all); i++){
            if ( all[i]->query("equipped") && all[i]->query("skill_type"))
                 return notify_fail("�������Ѿ�װ��������������\n");
            if ( all[i] == me->query_temp("mysnake",1) ) j=1;
        }
        if (j==0)  return notify_fail("��������ڲ��������ϣ�\n");  
        weapon= new(__DIR__"snakewhip");
        if (!weapon)  return notify_fail("�쳣����\n");
        exp=(me->query_temp("mysnake",1))->query("combat_exp");
        (me->query_temp("mysnake",1))->move(__DIR__"emptyroom");
        damage = random(exp/500);
        if(damage > 80) damage= 80;
        if(damage < 30) damage= 30;
        weapon->set("weapon_prop/damage", damage);
      weapon->set("rigidity",random(4)+6);
        weapon->move(me);
        if(!weapon->wield(me)){
           destruct(weapon);
           if(!((me->query_temp("mysnake",1))->move(me)))
              (me->query_temp("mysnake",1))->move(environment(me));
           return 0; 
        }
//      me->command("wield snakewhip");
        me->set_temp("wieldsnake",weapon);
        tell_object(me,"������װ�����Ϊ������\n"); 
        return 1;
}

int do_unwield(string arg)
{ 
	object me;
        me=this_player();
        if(me->query_temp("wieldsnake")==0)
                return notify_fail("������û���ý�����������\n");
        if(objectp(me->query_temp("wieldsnake",1))){
         me->query_temp("wieldsnake",1)->unequip();
         destruct(me->query_temp("wieldsnake",1));
        }
        me->delete_temp("wieldsnake");
        if(!((me->query_temp("mysnake",1))->move(me)))
                (me->query_temp("mysnake",1))->move(environment(me));
        tell_object(me,"��ж���˽��ߡ�\n"); 
        return 1;
}
