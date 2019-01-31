// NPC: /d/huashan/npc/yuebuqun.c
// Date: Look 99/03/25
// Modify by Looklove 2000,12,15

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
string ask_zhengqi();
string ask_zixia();
string ask_me1();
string ask_me2();
string ask_pay();

string ask_fail();

void create()
{
        set_name("����Ⱥ",({"yue buqun", "yue", "buqun" }));
        set("title","��ɽ�ɵ�ʮ����������");
        set("nickname","���ӽ�");
        set("long", "������ڽ���������Զ����������𣬻�ɽ�������ˡ�\n");
        set("age", 40);
        set("attitude", "peaceful");
        set("no_bark",1);
        set("shen_type", 1);
        set("per",25);
        set("pur",10);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi",3800);
        set("qi", 3800);
        set("max_jing", 2400);
        set("jing",2400);
        set("eff_jingli", 2700);
        set("jingli", 2700);
        set("max_neili", 5500);
        set("neili", 5500);
        set("jiali", 50);
        set("combat_exp", 2400000);
        set("score", 30000);
        set("chat_chance_combat",30);
        set("chat_msg_combat", ({
        (: perform_action, "sword.sanqingfeng" :),
        }));
// 48          set_skill("strike", 180);
// 49          set_skill("hunyuan-zhang", 180);
        set_skill("poyu-quan", 180);
        set_skill("cuff", 180);
        set_skill("sword",  180);
        set_skill("dodge",  180);
        set_skill("force",  180);
        set_skill("parry",  180);
        set_skill("literate",100);
        set_skill("zixia-gong", 180);
        set_skill("huashan-jianfa",  180);
        set_skill("huashan-shenfa",  180);
        set_skill("zhengqi-jue", 180);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
// 66          map_skill("strike","hunyuan-zhang");
        map_skill("cuff","poyu-quan");
// 68          prepare_skill("strike","hunyuan-zhang");
        prepare_skill("cuff","poyu-quan");
        create_family("��ɽ��",13,"����");

        set("inquiry", ([
              "��ϼ�ؼ�" : (: ask_zixia :),
              "ʧ��" : (: ask_fail :),
              "�Ͷ�����" : (: ask_me1 :),
              "����" : (: ask_me2 :),
              "������" : (: ask_zhengqi :),                        
//		"����" : (: ask_pay :),
        ]));

        setup();
        carry_object(BINGQI_D("sword/sword"))->wield();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }       
     
}

void greeting(object me)
{
        int shen;
         if(!me) return;
        shen = me->query("shen");
        if(shen <= -200000 && me->query("family/family_name") == "��ɽ��"){
        	command("chat* slap "+me->query("id"));
        	command("slap "+me->query("id"));
        	command("say ���������������а�����ӽ������㲻���ǻ�ɽ�����ˣ�");
        	command("expell " + me->query("id"));
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "��ɽ��"){
		command("sigh "+me->query("id"));
		command("say �ҿ����������������а��������ǲ�������������ʲô���£�");
		command("say ������Ҳ鵽�����������һ�ɽ�������£��Ҷ������㣡");
	}
}


string ask_pay()
{
        object me = this_player();
        mapping fam;

        fam = me->query("family");
        if (!fam || fam["family_name"] !="��ɽ��")
           return RANK_D->query_respect(me)+"��������ת�ɰɣ�BBB ���ǲ���׼��ġ�\n";
        if( me->query("hs/rec") )
           return RANK_D->query_respect(me)+"����Ҫ���������һ��ֻ��Ҫһ�Ρ�\n";

           me->set_skill("force", me->query("max_pot") - 100);
           me->set_skill("sword", me->query("max_pot") - 100);
           me->set("hs/rec", 1);

        return  "���ˣ���Ļ����ڹ�����������������Ŀǰ���������ˣ�����ȥ�� hunthu �� darken �ˡ�\n" ;
}


void attempt_apprentice(object ob)
{
        mapping fam;
        if ( mapp(fam=ob->query("family"))
         && (string)fam["family_name"] != "��ɽ��"  
         && (int)ob->query("is/huashan")==1 ) {
              message_vision(CYN "$N���������ɽ�ɵ���ͽ��������ʲô ������\n"NOR, ob );
              command("slap "+ob->query("id"));
              return;
        }
        if ( ob->query("gender") != "����" ){
              command("say ��ֻ����ͽ��" + RANK_D->query_respect(ob) + "��ذɡ�");
              return;
        }
        if ((int)ob->query("shen") < 0) {
              command("say �һ�ɽ�����������������ɣ��Ե���Ҫ���ϡ�");
              command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
              return;
        }
        command("say �ðɣ��Ҿ���������,���ҪΪ���ǻ�ɽ����������");
        ob->set("is/huashan",1);
        command("recruit " + ob->query("id"));
}

string ask_me1()
{
        int i;
        object ob, me, name1, ling;
        me=this_player();
        ob = this_object();
        ling = present("ling pai", me);
        name1 = me->query("id");
        i = me->query("shen");

        if (me->query("shen") < 10000)
           return "����¶�׹�, ����ȥ�Ͷ�����? "; 

        if (me->query_temp("hs/jobji"))
           return "�㲻�ܹ�˵ѽ������������ɼ����ҿ�����\n";

        if ((int)me->query("combat_exp") < 100000)
           return "���书δ�ɣ���ôΣ�յ������Ǳ����ˣ�\n";

        if (me->query("job_name") == "�Ͷ�����")
           return "����û����˵�ж���Ϊ�����գ����Լ�ȥ��ϰ�书ȥ�ɣ�";

        if(me->query_condition("job_busy"))
           return "��������æ�������������أ�";

        ob=new(__DIR__"obj/ling");
        ob->set("owner",getuid(me));
        me->set_temp("hs/jobji",1);
        command("nod "+me->query("id"));
        ob->move(me);
        ob->set_temp("hsjob", name1);
        ob->set_temp("job_busy",me->query_condition("hs_job"));
        me->set("job_name","�Ͷ�����");
        me->apply_condition("hs_job",25 + random(5));
        me->apply_condition("job_busy", 10);
        tell_object(me, HIC"����Ⱥ����һֻ���ơ�\n");
        return "��˵���ڻ�ɽ������������һЩ������ɧ�Ű��գ���ȥѲ��һ�£��������˲�������\n";
}

string ask_zhengqi()
{
        mapping fam;
        object me, ob;
        int shen, exp, i;
        me = this_player();
        ob = this_object();
        shen = (int)me->query("shen", 1);
        exp = (int)me->query("combat_exp", 1);
        i = (shen - exp);
        fam = me->query("family");
        if (!fam || fam["family_name"] !="��ɽ��")
           return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��\n";
        if( i < 1000 )
           return "�������֮����������ν���ָ�������������\n";
        if( (int)me->query_skill("zhengqi-jue", 1) < 150 )
           return "���������δ����򣬿������޷�ָ���㡣\n";
        if( (int)me->query_skill("zhengqi-jue", 1) > 200 )
           return "����������ѵ���򣬿������޷�ָ���㡣"; 
        if( (int)me->query("jing", 1) < 100 )
           return "����������״��̫���ˣ����޷������������ľ���֮����\n";
        if( (int)me->query("potential", 1) < 2 )
           return "������Ǳ�ܲ��㣬���޷�ָ���������������\n";
        me->improve_skill("zhengqi-jue", 100 + random(100));
        me->add("shen", -1000);
        me->add("potential", -1);
        me->receive_damage("jing", random(100));
        tell_object(me, HIC"��е����м���������������\n"NOR);
        return  "�ðɣ���Ȼ�����������������Ҿ�ָ����һ�¡�\n" ;
}

string ask_me2()
{
        return "��������أ�\n";
}
        
int accept_object(object me, object ling)
{
        object name1;
        int exp,pot,getshen,job_busy,total_job_times;
        name1 = me->query("id");

	if( ling->query("id") != "ling pai")
              return notify_fail("����Ⱥ˵��������ѽ����ɽ�ɾ�Ȼ������������ƭ�ӣ�\n");
        if( ling->query_temp("mmr") != name1 ){
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1));
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("����Ⱥ˵��������ô��ôû�ã�û��ȥ�ҵ�������\n");
        }
        if( ling->query_temp("hsjob") != name1 ) {
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1) * 5);
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("����Ⱥ˵���������������ô��\n");
        }
        if( (int)ling->query_temp("done", 1) < 2)
              return notify_fail("����Ⱥ˵�����㻹û���ʦ���������ء�\n");
        if ( !me->query_temp("hs/jobji"))
                {
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1) * 5);
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("����Ⱥ˵����������ƴ�����͵���ģ�\n");
                }
        if ( !me->query_condition("hs_job")){
                command("hmm "+ me->query("id"));
                me->add("shen", -(int)me->query("hs_job",1) * 5);
                me->delete_temp("hs/jobji");
                call_out("destroying", 1, ling);
                return notify_fail("����Ⱥ˵��������ôȥ����ô��ʱ�䣿\n");
         } 
        write("����Ⱥ���˿�������ơ�\n", me);
        command("thumb "+ me->query("id"));
        job_busy = (int)ling->query_temp("job_busy");
        command("say ����" + RANK_D->query_respect(me) + "�պ�������£����кñ���\n");
        if (job_busy > 4) command("say " + RANK_D->query_respect(me) + "��û��ǻ�ȥЪϢһ�°ɡ�\n");
        getshen = 100 + random((int)me->query("age",1)) + random((int)me->query("hs_job",1)/15);
        if( me->query("family") && me->query("family/family_name") =="�һ���") getshen = 0;
        me->add("shen", getshen );
        if (job_busy > 4)
        exp = 40 + random(20);
        else
        exp = 200 + random(50);
        if (exp < 30) exp = 30 + random(20);
        if (exp > 100) exp = 100 + random(20);
        me->add("combat_exp",exp);
        me->add("hs_job",1);
        pot= exp/5 + random(exp/6);
        if(( (int)me->query("potential", 1) + pot) > (int)me->query("max_pot", 1)){
           me->set("potential", (int)me->query("max_pot", 1));
        }
        if(( (int)me->query("potential", 1) + pot) <= (int)me->query("max_pot", 1)){
           me->add("potential", pot);
        }
//add log to HS_JOB_GIFT
        log_file("job/HS_JOB_GIFT",sprintf("%s %s(%s)%d������������%d��Ǳ��%d������%d��\n",
        ctime(time())[4..19],me->name(1),me->query("id"),(int)me->query("hs_job"),exp,pot,getshen));

        me->clear_condition("hs_job");
        me->delete_temp("hs/jobji");
        me->delete_temp("hs/have");
        call_out("destroying", 1, ling);
        write("������"+CHINESE_D->chinese_number(exp)+"�㾭�飬"
                +CHINESE_D->chinese_number(pot)+"��Ǳ�ܣ�"+CHINESE_D->chinese_number(getshen)+"������\n", me);
//�ݷ����������������ɽ�������400�Σ��ٸ��������200�Σ�ؤ���������200��
        total_job_times = me->query("hs_job") + me->query("dali_job") + me->query("gb_job");
        if ((random(me->query("hs_job")) >400
         && random(me->query("dali_job")) >400
         &&( random(me->query("gb_job")) >400 || random(me->query("combat_exp"))>2000000 )) 
         && !me->query("fengset")
         && me->query("family/family_name")=="��ɽ��"
         && total_job_times % 50 == 0
         && me->query("hs_job") < 2001){
                me->set_temp("mb",1);
                log_file("quest/jiujian",sprintf("%s %s(%s)��%d�λ�ɽ����ʱ��ɱ�������л�����˼���������ڡ�\n",ctime(time())[4..19],me->name(1),capitalize(me->query("id")),me->query("hs_job")));
                command("say "+me->query("name")+"��ɱ�˲��ٶ��ˣ�δ��ɱ�����ز�����˼���������ڰɡ�\n");
        }
        return 1;
}

string ask_zixia()
{
        mapping fam;
        object me;
        me = this_player();
        fam = me->query("family");
        if (!fam || fam["family_name"] !="��ɽ��")
           return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";
        if((int)me->query_skill("zhengqi-jue", 1) < 60 )
           return "���������δ��������ھ�������ϼ�ؼ���δ��Ϊʱ���硣";
        me->set_temp("hs/askzixia",1);
           return  "��ϼ�ؼ����һ�ɽ������ǰ��ʱ�䲻֪������δ��ˡ���ȥ�������ʦ�ְɡ�" ;
}

string ask_fail()
{
          object me,ling;
          me = this_player();
            ling = present("ling pai", me);
          if(! me->query_temp("hs/jobji"))
                  return "����û������񣬺�νʧ�ܰ���";
            if( ling && ling->query_temp("hsjob") == me->query("id"))
           destruct(ling);
          me->clear_condition("hs_job");
          me->clear_condition("job_busy");
          me->apply_condition("job_busy", 6+random(4));
          me->delete_temp("hs/jobji");
          me->delete_temp("hs/have");
                  return "��Ȼ��ˣ�Ҳ������ǿ����������°ɡ�";
}

void destroying(object ling)
{
	if (ling) destruct(ling);
}

void relay_emote(object me,string arg)
{
        command(arg+" "+me->query("id"));
}
