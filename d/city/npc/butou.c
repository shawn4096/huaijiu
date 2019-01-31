// butou.c ���ݲ�ͷ
// Modify by looklove 2001,4,19 fix moving_ob bug & add kill_ob killer��
// modified by olives@SJ 4/27/2001  set no_get����ֹ��
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("�ͷ", ({"li butou","butou","li","bu tou"}));
       	set("long",
                "һλ�������ݵĲ�ͷ����Ĳ��ߣ�������������\n"
                "��˵��������Ĳݿܶ��������֡�\n"
        );
       	set("nickname", HIR"���ݿ첶"NOR);
        set("gender", "����");
        set("attitude", "peaceful");
	
	set("no_get",1);//�������˱�ȥpk�������������
        set("age", 35);
        set("shen", 2000);
        set("str", 30+random(10));
        set("int", 20);
        set("con", 30);
        set("dex", 35);
        set("qi", 2500);
        set("max_qi", 2500);
        set("jing", 1400);
        set("max_jing", 1400);
        set("jingli", 3220);
        set("max_jingli", 3220);
        set("neili", 6500);
        set("max_neili", 3500);
        set("jiali", 120);
        set("combat_exp", 550000+random(200000));
        set("startroom","/d/city/guangchangbei");

        set_skill("force", 180);
	set_skill("blade",180);
	set_skill("cuff",180);
	set_skill("taizu-quan",180);
        set_skill("shenghuo-shengong", 180);
        set_skill("dodge", 180);
        set_skill("tiyunzong", 180);
        set_skill("parry", 180);
        set("chat_chance", 20);
        set("chat_msg", ({
               "��ͷͦ��ͦ�ظ�������Ц��������˵�������ˣ���ЩΪ������������һ���ŷ���ӡ� \n",
               (: random_move :)
       }) );

        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "taizu-quan");
        map_skill("cuff", "taizu-quan");
       	prepare_skill("cuff", "taizu-quan");

        setup();
        carry_object(ARMOR_D("armor"))->wear();
        carry_object(ARMOR_D("9xie"))->wear();
}

void init()
{
        object me, ob;

        ::init();

        ob = this_player();
        me = this_object();
        
        if (interactive(ob)
        && !wizardp(me)
        && !environment(ob)->query("no_fight")){
        	if((int)ob->query_condition("killer")>5){
        		command("say �����������㣬��ȴ�Լ����������ˣ�������\n");
        		command("stare "+ob->query("id"));
        		ob->start_busy(1);
         		me->set_leader(ob);
         		remove_call_out("kill_ob");
         		call_out("kill_ob", 1, ob); 
        	}
        	else if((int)ob->query("PKS",1) >40){
         		command("say ��˵��������˲��ٻ��£�����ͺͱ�����һ�ˣ�\n");
	 		ob->start_busy(1);
	 		remove_call_out("hiting_ob");
         		call_out("hiting_ob", 1, ob);
        	}
        }
}
int hiting_ob(object ob)
{
	object me = this_object();
    	
    	if (!ob) return 0;
	if (me->is_fighting())return 0;
	if(environment(ob)!=environment(me)) return 0;
	
	me->set_leader(ob);
        ob->fight_ob(me);
        me->fight_ob(ob);
	remove_call_out("moving_ob");
	call_out("moving_ob",1,ob);
}
int moving_ob(object ob)
{
	if (!ob) return 0;
       	if (!living(ob)&&present(ob, environment(this_object()))){
        	switch( random(3) ) {
		case 0:
	     		command("say  �����ܣ�֪���ٸ��������˰ɣ�");
		break;
		case 1:
			command("say  ���������ʵʵȥ���Űɡ�");
		break;
		case 2:
			command("nod");
		break;
		}
    		ob->move("/d/city/laofang"); 
        	ob->set("eff_jing",1);
	}
	else {
	remove_call_out("hiting_ob");
	call_out("hiting_ob",1,ob);
	}
}
void unconcious()
{
	remove_call_out("moving_ob");
	remove_call_out("hiting_ob");
	::unconcious();
	return ;
}
