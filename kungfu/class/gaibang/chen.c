// chen.c �³���
// Modify by Looklove@SJ 2000/9/27
// Update by Yanqi 10/04/2k
// MOdify By Looklove 2000/10/9

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

string ask_fangqi();
string ask_dan();
string ask_whip();
int ask_job();
int ask_trap();
string get_place(string str);
int check(object ob);

void create()
{
        set_name("�³���", ({"chen zhanglao", "chen", "zhanglao"}));
        set("title", "ؤ��Ŵ�����");
        set("nickname", "������");
        set("gender", "����");
        set("unique", 1);
        set("no_quest",1);
        set("no_bark",1);
        set("age", 56);
        set("long","����ؤ��������֮һ��ʹ����һֻ����������ǹ��졣\n");
        set("attitude", "peaceful");
        set("dan_count",200);
        
        set("str", 25);
        set("int", 23);
        set("con", 25);
        set("dex", 23);
        set("qi", 2100);
        set("max_qi", 2100);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 50);
        
        set("combat_exp", 700000);
        set("apprentice", 1);
        
        set_skill("force", 120); // �����ڹ�
        set_skill("huntian-qigong", 120); // ��������
        set_skill("unarmed", 120); // ����ȭ��
        set_skill("dodge", 140); // ��������
        set_skill("xiaoyaoyou", 140); // ǧ������ 
        set_skill("parry", 120); // �����м�
        set_skill("whip", 140);
        set_skill("begging", 110);
        set_skill("huifeng-bian", 140); 
        set_skill("suohou-shou",120);
        set_skill("hand",120);
        map_skill("hand","suohou-shou");
        map_skill("whip", "huifeng-bian");
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "huifeng-bian");
        prepare_skill("hand", "suohou-shou");
        
        set("chat_chance", 10);
        set("chat_msg_combat", ({
               (: perform_action, "whip.huixuan" :)
            }));

       
        create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "����" : "����Ķ���ȥ��\n",
                "����" : "������ϧ��ϧ���ǰ����ε�Ӣ�ۣ���ϧ�������֡�\n",
                "�ǰ���" : "�����������ǰ�����Ǵ�ү�����ѣ�\n"
                         "��������ؤ���ǰ�ΰ�����һ˫������ʹ�ó����뻯��\n"
                         "��˵����ǰÿ�춼Ҫ��ʮ����ʮ����¶ǣ�\n"
                         "Ȼ���ȥ���ƣ������˲���\n",
                "����" : "Ŷ�����������Ҳ��̫���������ʱ�����Ǹ��ɳ���ѧ�ġ�\n",
                "���߹�" : "�Ǻǣ���Ҳ��̫�������ȥ��͵���ˡ�\n",
                "׽��" : (: ask_job :),              
                "job" : (: ask_job :),
                "����" : (: ask_trap :),
                "����" : (: ask_fangqi :),
                "�ٲݵ�" : (: ask_dan :),
                "dan" : (: ask_dan :),
                "�Ʋ���" : (: ask_whip :),
        ]));
        setup();
        carry_object("/kungfu/class/gaibang/obj/bainayi")->wear();
        carry_object("/kungfu/class/gaibang/obj/gb_budai9")->wear();
}

void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }
        if ( ob->query_int() < 25 ) {
                command(":)");
                command("say " + RANK_D->query_respect(ob) +"�������ޣ�������ѧ���õġ�\n");
                return;
        }

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("ؤ���ܶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","�ܶ�");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}

void init()
{
        object me;
        me = this_player();
        
        ::init();
        if( interactive(me) && !is_fighting()&& me->query_temp("gb_snake/over"))
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
}

void greeting(object ob)
{
        object snake;
        int exp,pot,potmax,poto,j;
        object me;
        
        potmax = ob->query("max_pot");
        me = this_object();
        j = ob->query("snake_job");

        if( !ob || environment(ob) != environment() ) return;
        if (!ob->query_temp("gb_snake/start")
                || !ob->query_temp("gb_snake/over"))
                return;

        if ( ob->query_temp("gb_snake/over")){
                if ( present("du she",environment(ob) ) 
                        && ob->query_temp("gb_snake/start")){
                        snake = present("du she",environment(ob));
                        }
                else 
                snake=present("du she",ob);
        }

        if (!snake && ob->query_temp("gb_snake/start")
                && ob->query_temp("gb_snake/over"))
        {
                command("angry " + ob->query("id"));
                command("say ��ô�򵥵��¶��첻�ã�����ȥ�ɡ�");
                ob->delete_temp("gb_snake");
                ob->apply_condition("job_busy",2+random(3));
                return;        
        }       
        if (snake && snake->query_temp("name1")==ob->query("id")
                && ob->query_temp("gb_snake/over"))
        { 
	        ob->add("snake_job",1);
                ob->delete_temp("gb_snake");
                
                exp = 200 + random(100);
                pot = exp/5 + random(exp/6);

             if (ob->query("snake_job") < 2000 || ob->query("combat_exp",1) < 2000000) {
                tell_object(ob, HIY"������"+CHINESE_D->chinese_number(exp)+"�㾭���"+CHINESE_D->chinese_number(pot)+"��Ǳ�ܡ�\n"NOR);
                ob->add("combat_exp",exp);
                ob->add("potential",pot);
		poto = ob->query("potential");
                if (poto > potmax) ob->set("potential", potmax);
                write_file( "/log/job/snake_job",sprintf("%s %s(%s)��%d��׽��������%d�㾭�飬%d��Ǳ�ܡ�\n",
                        ctime(time())[4..18],ob->name(),ob->query("id"),ob->query("snake_job"),exp,pot));
             } else
                write_file( "/log/job/snake_job",sprintf("%s %s(%s)��%d��׽������û�еõ���������ǰ���飺%d\n",
                        ctime(time())[4..18],ob->name(),ob->query("id"),ob->query("snake_job"),ob->query("combat_exp")));

                command("nod " +ob->query("id"));
                message_vision(HIM"�³��ϴ�$P����ӹ��ߣ�ת��װ��һ���ڴ��\n"NOR,ob);
                message_vision(HIW"$N�ܹ�׽��"+CHINESE_D->chinese_number(ob->query("snake_job"))+"���ߡ�\n"NOR,ob);
                destruct(snake);
                ob->apply_condition("job_busy",3+random(3));
        }
        if(!ob->query("gb/snaked") && j>1000){
                if(random(j)>1000 && !ob->query("gb/snake")) {
                        command("whisper " +ob->query("id")+" �벻��ѧ���ߣ�");
                        message_vision(HIM"�³��ϴӲ������ó�һ��С�ߡ����˸����ڣ�ֻ��С���������赸״������ض���\n"NOR,ob);
                        command("say �������ɣ�������������˽��Ժ��ҽ������ߵı��¡�");
                        command("pat " +ob->query("id"));
                        ob->set("gb/snake",1);
                        return;
                }

/*
                if(random(j)>2000 && ob->query("gb/snake")){
                        command("thumb " +ob->query("id"));
                        command("say �����Ͻл��Ҹ�����ˣ�����һ�����ֵı��¡�");
                        message_vision(HIM"�³��ϴӲ������ó�һ��С�ߡ����˸����ڣ�ֻ��С���������赸״������ض���\n"NOR,ob);
                       	message_vision(HIM"�³��ϵݸ�$Pһ�����ӡ�\n"NOR,ob);
        		new("/clone/misc/gbzshao")->move(me);
                	command("whisper " +ob->query("id")+" ���...���...��ϸ�����ӡ�");
                        message_vision(HIM"$P����������ͷ����ʦ�����Լ��ǣ�ĳ������é��ٿ���\n"NOR,ob);
                        command("whisper " +ob->query("id")+" ��ȥ�置��ɽ���������г�ȥ���Ǹ��ط�ץ�����Լ���ɡ�");
                        ob->set("gb/snaked",1);
                        return;
                }
*/
                command("say �������ɣ�������������˽��Ժ��ҽ������ߵı��¡�");
        }
        return;
}

int ask_job()
{
        object me,ob,name1,target,*living,where;
        string str;
        int i,j;
        me = this_player();
        
        if (me->query("family/family_name")!="ؤ��" ){
                command("say ����������ˣ���������µ��Ӷ����ڿ졣");
                return 1;
        }
        if (me->query("snake_job")>=2100 && me->query("combat_exp")>2000000){
                command("say �������ͷ�����㹻�ˣ�����ȥ�ɡ�\n");
                return 1;
        }
        if (me->query("combat_exp") < 100000){
                command("say �ҿ��㱿�ֱ��ŵģ���ȥ��������ɡ�\n");
                return 1;
        }
        if (me->query_temp("gb_snake/start")){
                command("say �ղŲ����������ץ��ȥ��������ô����ȥ��\n");
                return 1;
	}
        if (me->query_condition("job_busy")){
                command("say ����ͷ�����������°ɣ���һ�������ɣ�\n");
                return 1;
        }
        if( me->query("job_name") =="ؤ��ץ��"){
        	command("say ���ץ���ߣ�������ȥ��Ϣһ��ɡ�");
        	return 1;
        }

        living = livings();
        for (i=0;i < sizeof(living);i++){
                j = random(sizeof(living));
                if (j <= 1 || j == sizeof(living) -1) continue;
                if(check(living[j]) ){
                        target = living[j];
                        str = environment(target)->query("short");
                        where = environment(target);
                        if( str == "��ɮ��" 
                         || str == HIR"������"NOR
                         || str == "��շ�ħȦ" ) continue;
                        if( get_place(base_name(environment(target)))!="" ) break;
                }
        } 

        if( !target )
                return notify_fail("�³�����ʱ����ץ�ߣ����һ��������ɡ�\n");

        me->set_temp("gb_snake/start", 1);
        me->set_temp("gb_snake/where",get_place(base_name(environment(target)))+environment(target)->query("short"));
        me->apply_condition("job_busy", 9);
        me->set("job_name", "ؤ��ץ��");
        ob = new("/clone/animal/snake");
        name1 = me->query("id");
        ob->set_temp("name1",name1);
	ob->move(where);
        message_vision(CYN"�³���˵����$Nȥ"+me->query_temp("gb_snake/where")+CYN"��������׽���߻����ɣ�\n"NOR,me);
        return 1;
}

int ask_trap()
{
        object ob, me = this_player();
        int i, j;
        object *obj;
        int x,y =0;

        if (present("qing she", me) || query("snake/"+me->query("id")) >0){
           command("say ��Ҫ��");
           command("heng");
           return 1;
        }
        obj = objects();
        x = sizeof(obj);
        while(i--) {
            if ( obj[i]->query("id") =="qing she" && obj[i]->query("owner") == me->query("id"))
            y++;
        } 
        if(y > 0){
           command("say ��Ҫ��");
           command("heng");
           return 1;
        }
        if (me->query("snake_job")<2000){
           command("say �����ץ���ߣ��Ҳŷ���һЩ��");
           command("rascal");
           return 1;
        }
        j = random(3)+2;
        j = 1;
        for (i=0;i<=j;i++){
          ob = new("/clone/animal/trap-snake");
          ob->move(me);
          ob->set("owner",me->query("id"));
        }
        message_vision(HIG"$N����$n����С���ߡ�\n"NOR,this_object(),me);
        me->add("snake_job",-j*2);
        add("snake/"+me->query("id"), 1);
        return 1;
}

string ask_fangqi()
{
        object me;

        me = this_player();
        
        if(me->query("family/family_name")!="ؤ��")
              return "�����ؤ��Ӣ��,������Ϲ����ʲ��?";
        if(!me->query_temp("gb_snake/start"))
              return "ʲô��������ʲô����";

        me->delete_temp("gb_snake");
        me->clear_condition("job_busy");
        me->start_busy(3);
        me->apply_condition("job_busy",6+random(6));
        return "��ﲻ���ң������ȥ�����ɡ��Ժ��������㡣";
}

string ask_dan()
{
        object me,ob;
        me = this_player();

         if(me->query("family/family_name")!= "ؤ��")
                return "��ȥ��ҽ���ɣ��ҿ�û�취��";
         if(query("dan_count") < 1)
                return "�������ˣ��ٲݵ�ȫ�������ˣ���ȥ�Լ��Ҵ��ɡ�";
        if (present("bai caodan", me))
                return RANK_D->query_respect(me) + 
                "�ٲݵ�����������ϻ��У�������һЩ�����������ֵܰɣ�ؤ������������";
        if(me->query("snake_job")>100){
                ob = new("/d/gb/npc/obj/bcd");
                ob->move(me);
                message_vision("�³��ϸ�$Pһ�Űٲݵ���\n",me);
                return "�����������ô���æ�ķ��ϣ��Ҿ͸���һ�š�";
        }
         if((int)me->query("eff_jing",1)==(int)me->query("max_jing",1))
                return "�����û���ж����������ʲô��";

        add("yao_count", -1);
        ob = new("/d/gb/npc/obj/bcd");
        ob->move(me);
        message_vision("�³��ϸ�$Pһ�Űٲݵ���\n",me);
        return "��������һ�Űٲݵ����ƽ��߳��Ӷ�����֪�Ƿ����֢����";
}

string ask_whip()
{
        object me,ob;
        me = this_player();

        if (me->query("family/family_name")!="ؤ��")
              	return "�����ؤ��Ӣ��,������Ϲ����ʲ��?";
        if ( present("po budai", this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "�Ʋ������������ϣ�";
        if ( present("mumian jiasha", environment()) )
                return RANK_D->query_respect(this_player()) + 
                "�Ʋ���������������ȡ�ߡ�";
        ob = unew(BINGQI_D("pobudai"));
        if(!clonep(ob)) return "��Ǹ���������ˣ��Ʋ����Ѿ�����ȡ���ˡ�";
        
        if(clonep(ob) && ob->violate_unique()){
           	destruct(ob);
           	return "��Ǹ���������ˣ��Ʋ����Ѿ�����ȡ���ˡ�";
        }            
        ob->move(this_player());
        message_vision("\n�³��ϵݸ�$Nһ���Ʋ�����\n\n", this_player());
        return "����Ʋ�����������ˣ�";
}

string get_place(string str)
{ 
        string *place = explode(str, "/");

        str = "";
        if(place[0] == "d")
                switch(place[1]){
	                case "baituo":    str = "�������ɽ";  break;
                        case "hj":        str = "����ؽ�"; break;
                        case "mingjiao":  str = "��������"; break;
                        case "shaolin":   str = "������ɽ����"; break;
                        case "songshan":  str = "������ɽ"; break;
                        case "wudang":    str = "�����䵱ɽ"; break;
                        case "xingxiu":   str = "�������޺�"; break;
                        case "city":      str = "�������ݳ�"; break;
                        case "emei":      str = "�Ĵ�����ɽ"; break;
                        case "fuzhou":    str = "�Ͻ�����"; break;
                        case "jiaxing":   str = "���ϼ���"; break;
                        case "taishan":   str = "ɽ��̩ɽ"; break;
                        case "dali":      str = "���ϴ����"; break;
                        case "tls":       str = "����������"; break;
                        case "tiezhang":  str = "��������ɽ"; break;
                        case "kunlun":    str = "";break;
                        case "fairyland": str = ""; break;
                        case "gumu":      str = ""; break;
                        case "chengdu":   str = "�Ĵ��ɶ�"; break;
                        case "huashan":   str = "������ɽ"; break;
                        case "xiangyang": str = "��������"; break;
                        case "xueshan":   str = "������ѩɽ"; break;
                        case "wizard":    str = ""; break;
                        case "death":     str = ""; break;
                        case "gaibang":   str = "ؤ��ֶ�"; break;
                        case "hz":        str = "���Ϻ���"; break;
                        case "village":   str = "����С��"; break;
                        case "wuguan":    str = "�������"; break;
                        case "thd":       str = ""; break;
                        case "gaibang":   str = "ؤ��ֶ�"; break;
                        case "mr":        str = "����������"; break;
                        case "suzhou":    str = "�����س�"; break;
                        case "sld":       str = "����������"; break;
        }
        return str;
}

string *no_kill_list = ({
         "mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int check(object ob)
{
        object room;
        string room_name;
        
        if(!objectp(ob)
         || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
         || ob->query("env/invisibility")
         || ob->query("no_quest")
         || member_array(ob->query("id"), no_kill_list) != -1
         || userp(ob)
         || ob->query("attitude")=="aggressive"
         || ob->query("have_master")
         || ob->query("env/wimpy")
         || !objectp(room=environment(ob))
         || !room->query("outdoors")
         || room->query("no_fight") 
         || room->query("outdoors") == "���ش��"
         || strsrch(room_name = file_name(room),"/d/") != 0
         || strsrch(room_name, "/d/wizard/") == 0
         || strsrch(room_name, "/d/wuguan/") == 0
         || strsrch(room_name, "/d/death/") == 0
         || strsrch(room_name, "/d/kunlun/") == 0
         || strsrch(room_name, "/d/mingjiao/lsd/") == 0
         || strsrch(room_name, "/d/mingjiao/bhd/") == 0
         || strsrch(room_name, "/d/shaolin/liwu") == 0
         || strsrch(room_name, "/d/shaolin/houyuan") == 0
         || strsrch(room_name, "/d/huashan/jiabi") == 0
         || strsrch(room_name, "/d/shaolin/fumoquan") == 0
         || strsrch(room_name, "/d/shaolin/xinchan") == 0
         || strsrch(room_name, "/d/mingjiao/yuanzi") == 0
         || strsrch(room_name, "/d/mingjiao/wxiang") == 0
         || strsrch(room_name, "/d/baituo/") == 0
         || strsrch(room_name, "/d/thd/") == 0
         || strsrch(room_name, "/d/sld/") == 0) 
         return 0;
        return 1;
}
