
#include <ansi.h>;
inherit NPC;

void throwing();
int do_kill(object me, object dest);
int give_weapon();
void create()
{
       	set_name("��ѩ��", ({ "xia xueyi", "xia", "xueyi" }) );
       	set("nickname", HIY"�����ɾ�"NOR);
       	set("gender", "����" );
       	set("shen_type", 1);
       	set("age", 23);
       	set("str", 34);
       	set("con", 28);
       	set("int", 27);
       	set("dex", 34);
       	set("per", 30);
       	set("location", 1);
       	set("shen", -50000);
       	set("long",@LONG
������ĸ�������ò���ڡ�����ʱȫ�Ҳ��ұ��¼���
�Ͻ������ţ���־���𡣴�������Ź֣�Ϊ�����ݣ�
�书���������˰�����Ѳ⡣������������������Ϊ
֮ɫ�䣬���ǳ������Ѳ�����\
LONG);
       	set("combat_exp", 2500000);
       	set("attitude", "heroism");
       	set("max_qi", 6000);
        set("unique", 1);
       	set("max_jing", 5000);
       	set("eff_jingli", 3000);
       	set("neili", 10000);
       	set("max_neili", 10000);
       	set("jiali", 70);
       	set_skill("force", 260); 
       	set_skill("medicine", 130); 
       	set_skill("hunyuan-yiqi", 260); 
       	set_skill("literate", 200);
       	set_skill("jinshe-jianfa", 260);
       	set_skill("jinshe-zhangfa", 260);
       	set_skill("sword", 260);
       	set_skill("dodge", 260);
       	set_skill("parry", 260);
       	set_skill("strike", 260);
       	set_skill("xinyuegong", 260);        

       	set("chat_chance_combat", 30);
       	set("chat_msg_combat", ({
                (: perform_action, "sword.kuangwu" :),
                (: throwing :),
	}));
	set("chat_chance", 35);
     	set("chat_msg", ({ (: random_move :), }));
     
        map_skill("force", "hunyuan-yiqi");
        map_skill("strike", "jinshe-zhangfa");
        map_skill("dodge", "xinyuegong");
        map_skill("parry", "jinshe-zhangfa");
        map_skill("sword", "jinshe-jianfa");
        prepare_skill("strike", "jinshe-zhangfa");
        
        set_temp("apply/armor", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/damage", 70);
        set_temp("apply/attack", 80);
        setup();
        
	if (clonep()) {
		UPDATE_D->get_cloth(this_object());
		add_money("gold", 2);
		give_weapon();
		call_out("do_back", 300+random(200), this_object());    
	}
}

int give_weapon()
{
	object sword, weapon;
	if (clonep(this_object())) {
		if(!objectp(weapon = this_object()->query_temp("weapon"))){
                        sword = unew(BINGQI_D("sword/jinshesword"));
                	if(!sword) sword = unew(BINGQI_D("changjian1")); 
                	sword->move(this_object());
                	sword->wield();                	
                }
		else if(weapon->query("id") != "jinshe sword" && 
                        objectp(sword = unew(BINGQI_D("sword/jinshesword")))) {
                		weapon->unequip();
                		destruct(weapon);  
                		sword->move(this_object());
                		sword->wield();
                }
                 
                if(objectp(sword = unew(BINGQI_D("throwing/jinshe-zhui"))) )
                	sword->move(this_object());
                if(!objectp(sword = present("zhuihun biao", this_object()))
                || sword->query_amount() < 2 )
                	carry_object(BINGQI_D("zh_biao"));    
        }   
}

void init()
{
        object ob, me;
        me = this_object();
        ::init();
        if (interactive(ob = this_player()) && !wizardp(ob) && !is_fighting()){
        	remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }      
        add_action("do_look",({"look", "consider", "smash", "kick", "kick2", "cut", "flirt", "lean"
        			"love", "interest", "kiss" })); 
}

int do_look(string target)
{
        object me;
 
 	if( !target ) return 0;
        me = this_player();
        
        if (id(target) && (string)me->query("gender") != "Ů��" && !is_busy() && !wizardp(me)) {
        	message("vision",HIR "��ѩ��ӥ��һ���������"+RANK_D->query_rude(me)+"��������\n"NOR, environment(), this_object() );
                if(present("zhuihun biao", me))
        		command("throw biao at " + me->query("id"));
        	else COMBAT_D->do_attack(this_object(), me, this_object()->query_temp("weapon"),1);
        }
        return 0;
} 

void greeting(object ob)
{
        object me = this_object();
        
        if(!me || !ob || environment(ob) != environment(this_object())) return;
        
        if( ob->query("combat_exp") > 800000 && ob->query("gender") != "Ů��") 
           	ob->add_temp("xiaxueyi_meet", 1);

        if(present("jinshe sword", ob) && !environment(me)->query("no_fight")){      
               	message_vision( CYN"\n$NͻȻ����$n���£���������Ľ�������\n"NOR,me,ob); 
               ob->start_busy(1); 
               	do_kill(me, ob);                                              
        }
        	
        if( me->is_busy() || me->is_fighting()) return;
        	
        else if(ob->query_temp("xiaxueyi_meet") > 2 && !environment(me)->query("no_fight")){
        	message_vision( CYN"\n$N�����ָ��$n���˹�����"+RANK_D->query_rude(ob)+"���������ү�����棡��\n"NOR,me,ob);
                ob->start_busy(random(2)); 
        	ob->delete_temp("xiaxueyi_meet");
               	me->fight_ob(ob);
		ob->fight_ob(me); 
        }
}

void throwing()
{     
	switch(random(2)) {
       		case 0 : command("throw zhui"); break;
       		case 1 : command("throw biao"); break;
     	}
}

void kill_ob(object me)
{     
      command("perform kuangwu");
      ::kill_ob(me);

}

string get_user_place(int i)
{
	object *obs = users(), ob, room;
	
	i++;
	if( i > 10 ) return 0;
	
	ob = obs[random(sizeof(obs))];	
	room = environment(ob);
	
	if (wiz_level(ob)
	|| ob->is_ghost()
        || !room
        || room->query("no_fight")
        || strsrch(file_name(room),"/d/") < 0 
        || !strsrch(base_name(room), "/d/wizard/")
        || !strsrch(base_name(room), "/d/death/")
        || !strsrch(base_name(room), "/d/wuguan/")) 
        	return get_user_place(i);

	else return file_name(room);
                
}
int do_back(object me)
{    
	string room;
	
  	remove_call_out("do_back");
  	if (!stringp(room = get_user_place(0)))   	
  		me->move("/d/huashan/shanlu1");  
  	else me->move(room);  
  	                     
  	tell_room(environment(me), me->query("name")+"�첽���˹�����\n", ({me}));	
  	me->set_leader(0);
  	give_weapon();
  	me->reincarnate();
  	return 1;
}

int checking(object me, object dest)
{
	object ob;
        if (!me || !dest || !present(dest, environment(me))) return 0;
	if (me->is_fighting(dest)){
	   	call_out("checking", 1, me, dest);
           	return 1;
	}
	   
	if( objectp(ob = present("corpse", environment(me)))
	  && ob->query("victim_name") == dest->query("name") ){
           	remove_call_out("checking");
           	if( objectp(dest = present("jinshe sword", ob)))
           		destruct(dest);  
           	command("chat* grin corpse");
           	tell_room(environment(me), me->query("name")+"������һ�ڣ��첽���˳�ȥ��\n" NOR, ({me}));
  	   	call_out("do_back", 1, me);
           	return 1;
   	}
   	   
	return 1;
}

int do_kill(object me, object dest)
{
	if( objectp(dest) && present(dest, environment(me))){
		me->set_leader(dest);
		me->kill_ob(dest);
		dest->fight_ob(me);
		checking(me, dest);
	}
	
	return 1;
}

