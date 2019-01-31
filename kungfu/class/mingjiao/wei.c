// NPC wei.c ΤһЦ
// Modify By River@SJ 99.06
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string *drugs = ({
       MEDICINE_D("sanhuang"),
       MEDICINE_D("huiyang"),
       MEDICINE_D("yuling"),
       MEDICINE_D("yuzhen"),
       MEDICINE_D("tianwang"),
});

void destroy(object ob);
void create()
{
        set_name("ΤһЦ",({"wei yixiao","wei","yixiao"}));
        set("title","���̻��̷���");
        set("nickname",GRN"��������"NOR);
        set("long", "�������̵��Ĵ󻤷�֮һ������������\n"+
                    "����ĸߴ�������ˣ�����һ����Ṧ��\n");
        set("age", 51);
        set("attitude", "peaceful");
        set("shen", -12000);
        set("str", 26);
        set("int", 26);
        set("con", 25);
        set("dex", 45);        
        set("max_qi", 3000);
        set("max_jing", 2400);
        set("eff_jingli", 2000);
        set("jiali", 70);
        set("combat_exp", 1200000);
        set("unique", 1);

        set_skill("strike",180); 
        set_skill("literate",110);
        set_skill("dodge",190);
        set_skill("force", 150);
        set_skill("piaoyi-shenfa", 190);
        set_skill("hanbing-mianzhang",180);
        set_skill("shenghuo-shengong", 140);
        set_skill("parry", 150);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("strike", "hanbing-mianzhang");
        map_skill("parry", "hanbing-mianzhang");
        prepare_skill("strike","hanbing-mianzhang");

        create_family("����",36,"����");
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "strike.xixue":),
        }));
        setup();
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
}


void init()
{
	::init();
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping fam = ob->query("family");
        mapping my_fam = me->query("family");
        if(!fam || fam["family_name"] != "����"){
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }
        if(fam["master_name"] == "���޼�"){
                command("haha");
                command("say "+RANK_D->query_respect(ob)+"���ǽ����״����ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
        }
        if (fam["generation"] == my_fam["generation"]){
                command("shake");
                command("say "+RANK_D->query_respect(ob)+"�Ѱݹ���ʹΪʦ��"+RANK_D->query_self(me)+"����������Ϊͽ��");
                return;
        }        
        if ((int)ob->query_skill("shenghuo-shengong", 1) < 100) {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��"); 
                command("say " + RANK_D->query_respect(ob)+"�Ƿ�Ӧ����ʥ�����϶��µ㹦��");
                return;
        }        
        if ((int)ob->query_skill("dodge",1) < 100) {
                command("say ��ѧ�ҵ��Ṧ����������һ�����Ṧ������");
                command("say ���Ṧ���棬" + RANK_D->query_respect(ob)+"�Ƿ����ò�����");
                return;
        }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
        command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
        command("recruit " + ob->query("id"));
        ob->set("title", this_object()->query("title")+"���½���");
}

int accept_object(object who, object ob,object me)
{
//      object drug;
        int exp,job,pot,bonus,gold, i, j =0;
        object* ppl;

        me = this_object();
        if(ob->query("name") != "Ѳ����" || ob->query("id") != "xunluo ling") {
               command("? "+who->query("id"));  
               return 0;
        }
        if(ob->query("owner") != who->query("id")){
               command("say �ߣ������Ǵ���͵���ģ�");
               call_out("destroy", 1, ob);  
               return 1;
        }
        if(!ob->query("task_ok")){
               command("say �������㻹�����ø�����»�ɡ�");
               command("pat "+who->query("id"));  
               return 0;
        }
        if(!who->query_condition("mj_xunluo")){
               command("say ��ô��ʱ�䣬�㶼����ȥ�ˣ�");
               command("disapp "+who->query("id"));
               call_out("destroy", 1, ob);  
               return 1;
        }
        command("nod");
        command("say Ը�������������е��Ӷ�����ڷ����ϣ�");
//      message_vision("\n$Nȡ��һ��ҩ�轻��$n��\n",me, who);
//      drug = new(drugs[random(sizeof(drugs))] );
//      drug->move(who);
        bonus = who->query_temp("mj/attacker1");
        if(bonus > 7) bonus = 7;
        exp = 400 + random(350)+ bonus * 50;
        job = who->query("mingjiao_job");
        gold = job/70 + random(job/70);
        if( gold < 1) gold = 1;
        if( gold > 15) gold = 14 + random(3);
        if (job < 2001) who->add("combat_exp",exp);
        if (job > 2001 && job < 3001) who->add("combat_exp",exp*2/3);
        if (job > 3001) pot=600/6+random(600/10);
        else
         pot= exp/5 + random(exp/6);
        who->add("potential", pot);
        who->add("mingjiao_job", 1);
        who->delete_temp("mj/attacker1");
        who->delete_temp("mj/over");
        if(who->query("potential") > who->query("max_pot")) 
           who->set("potential", who->query("max_pot"));
        MONEY_D->pay_player(who, gold * 10000);
        message_vision("\n$N����$nһЩ"HIY"�ƽ�"NOR"��\n"NOR,this_object(),who);
        command("whisper "+who->query("id")+" �������ˣ���Щ������ȥ�úÿ��һ���ɡ�");
        tell_object(who,"���Ѿ�Ϊ�������"+chinese_number(job)+"�ι����ˣ��ٺú�Ŭ���ɡ�\n");
        log_file("job/mj_job",sprintf("%s %s(%s)%d������������%d��Ǳ��%d�����ھ���%d��\n",
                ctime(time())[4..19],who->name(1),who->query("id"),job,exp,pot,who->query("combat_exp")));
        call_out("destroy", 1, ob);
        i = sizeof(ppl);
        while(i--) {
            if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query("jiuyang/wei"))
            j++;
        } 
        if( random(job) > 200
         && job < 3001
         && job %50 == 0
         && random(who->query_int()) >= 30
         && random(who->query_dex()) >= 30
         && random(who->query("kar")+ who->query("pur")+ who->query("per")) >= 30
         && j < 40
         && !who->query("jiuyang/wei")){
          command("whisper "+who->query("id")+" ���ȥ�Ž�������һ�Σ���������ʲô����Ҫ�����㡣");
          log_file("quest/jiuyang",sprintf("%s %s(%s)�����������%s�ε�ʱ�򣬵õ�ΤһЦ��ָʾ�������йؾ����񹦵Ĵ��š�\n",
            ctime(time())[4..19],who->name(1), capitalize(getuid(who)),chinese_number(job)));
          who->set("jiuyang/wei", 1);
        }
        return 1;
}

void destroy(object ob)
{
        destruct(ob);
        return;
}

int do_kill(string arg)
{
        object ob,ob2; 
        object me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;

        
        if (userp(ob)&& ob->query("family/family_name") == "����") {
                if (me->query("family/family_name") == "����") { 
        message_vision(ob2->name()+"��$N�ȵ�����Ϊ���̵��ӣ���Ȼɱ�Լ���ͬ�ţ��������㣡\n", me);
                }
                else {
                        message_vision(ob2->name()+"��$N�ȵ����󵨿�ͽ����Ȼ����������Ұ��\n", me);
                        kill_ob(me);
                }
                me->set("vendetta/����", 1);
                return 1;
        }
        return 0;
}


