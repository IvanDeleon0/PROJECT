/* =========================================================
   NODE template — behavior
   ========================================================= */

document.addEventListener('DOMContentLoaded', () => {
  initNav();
  initSignalCanvas();
  initHeroReadout();
  initScrollReveal();
  initStatCounters();
  initCtaForm();
  initToTop();
});

/* ---------------------------------------------------------
   Mobile nav
--------------------------------------------------------- */
function initNav(){
  const burger = document.getElementById('burger');
  const mobile = document.getElementById('navMobile');
  if(!burger || !mobile) return;

  burger.addEventListener('click', () => {
    const isOpen = mobile.classList.toggle('open');
    burger.setAttribute('aria-expanded', String(isOpen));
    burger.classList.toggle('is-active', isOpen);
  });

  mobile.querySelectorAll('a').forEach(link => {
    link.addEventListener('click', () => {
      mobile.classList.remove('open');
      burger.setAttribute('aria-expanded', 'false');
    });
  });
}

/* ---------------------------------------------------------
   Signature element: animated "signal network" canvas
   Nodes drift slowly; nearby nodes connect with lines;
   occasional pulses travel along a connection like a packet.
--------------------------------------------------------- */
function initSignalCanvas(){
  const canvas = document.getElementById('signalCanvas');
  if(!canvas) return;
  const ctx = canvas.getContext('2d');

  const reduceMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;

  let width, height, dpr;
  let nodes = [];
  let pulses = [];
  const LINK_DIST = 150;
  const NODE_COUNT_BASE = 70; // per 1,000,000 px^2 approx, scaled below

  function resize(){
    const rect = canvas.parentElement.getBoundingClientRect();
    dpr = Math.min(window.devicePixelRatio || 1, 2);
    width = rect.width;
    height = rect.height;
    canvas.width = width * dpr;
    canvas.height = height * dpr;
    canvas.style.width = width + 'px';
    canvas.style.height = height + 'px';
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    seedNodes();
  }

  function seedNodes(){
    const area = width * height;
    const count = Math.max(24, Math.min(90, Math.round((area / 1000000) * NODE_COUNT_BASE)));
    nodes = Array.from({ length: count }).map(() => ({
      x: Math.random() * width,
      y: Math.random() * height,
      vx: (Math.random() - 0.5) * 0.18,
      vy: (Math.random() - 0.5) * 0.18,
      r: Math.random() * 1.4 + 0.8
    }));
  }

  const mouse = { x: -9999, y: -9999, active: false };
  canvas.parentElement.addEventListener('mousemove', (e) => {
    const rect = canvas.parentElement.getBoundingClientRect();
    mouse.x = e.clientX - rect.left;
    mouse.y = e.clientY - rect.top;
    mouse.active = true;
  });
  canvas.parentElement.addEventListener('mouseleave', () => { mouse.active = false; });

  function maybeSpawnPulse(links){
    if(links.length === 0) return;
    if(Math.random() > 0.02) return;
    const link = links[Math.floor(Math.random() * links.length)];
    pulses.push({ a: link.a, b: link.b, t: 0, speed: 0.012 + Math.random() * 0.01 });
  }

  function draw(){
    ctx.clearRect(0, 0, width, height);

    const accent = 'rgba(61, 125, 251,';
    const accent2 = 'rgba(23, 224, 195,';

    // update positions
    nodes.forEach(n => {
      n.x += n.vx;
      n.y += n.vy;
      if(n.x < -20) n.x = width + 20;
      if(n.x > width + 20) n.x = -20;
      if(n.y < -20) n.y = height + 20;
      if(n.y > height + 20) n.y = -20;

      if(mouse.active){
        const dx = n.x - mouse.x, dy = n.y - mouse.y;
        const dist = Math.sqrt(dx*dx + dy*dy);
        if(dist < 120){
          const force = (120 - dist) / 120 * 0.03;
          n.vx += (dx / (dist || 1)) * force * 0.02;
          n.vy += (dy / (dist || 1)) * force * 0.02;
        }
      }
      // gentle velocity damping so it doesn't run away
      n.vx *= 0.995;
      n.vy *= 0.995;
    });

    // draw links
    const links = [];
    for(let i = 0; i < nodes.length; i++){
      for(let j = i + 1; j < nodes.length; j++){
        const a = nodes[i], b = nodes[j];
        const dx = a.x - b.x, dy = a.y - b.y;
        const dist = Math.sqrt(dx*dx + dy*dy);
        if(dist < LINK_DIST){
          const alpha = (1 - dist / LINK_DIST) * 0.35;
          ctx.strokeStyle = accent + alpha + ')';
          ctx.lineWidth = 1;
          ctx.beginPath();
          ctx.moveTo(a.x, a.y);
          ctx.lineTo(b.x, b.y);
          ctx.stroke();
          links.push({ a, b });
        }
      }
    }

    // pulses traveling along random links
    if(!reduceMotion) maybeSpawnPulse(links);
    pulses = pulses.filter(p => p.t <= 1);
    pulses.forEach(p => {
      p.t += p.speed;
      const x = p.a.x + (p.b.x - p.a.x) * p.t;
      const y = p.a.y + (p.b.y - p.a.y) * p.t;
      ctx.beginPath();
      ctx.arc(x, y, 2.2, 0, Math.PI * 2);
      ctx.fillStyle = accent2 + '0.9)';
      ctx.shadowColor = 'rgba(23, 224, 195, 0.8)';
      ctx.shadowBlur = 8;
      ctx.fill();
      ctx.shadowBlur = 0;
    });

    // draw nodes
    nodes.forEach(n => {
      ctx.beginPath();
      ctx.arc(n.x, n.y, n.r, 0, Math.PI * 2);
      ctx.fillStyle = accent + '0.55)';
      ctx.fill();
    });

    if(!reduceMotion){
      requestAnimationFrame(draw);
    }
  }

  window.addEventListener('resize', debounce(resize, 200));
  resize();
  draw();
  if(reduceMotion){
    // draw a single static frame, then stop
    draw();
  }
}

function debounce(fn, wait){
  let t;
  return (...args) => {
    clearTimeout(t);
    t = setTimeout(() => fn(...args), wait);
  };
}

/* ---------------------------------------------------------
   Hero readout — quick portfolio facts (edit the values below)
--------------------------------------------------------- */
function initHeroReadout(){
  const latencyEl = document.getElementById('rLatency');
  const nodesEl = document.getElementById('rNodes');
  const uptimeEl = document.getElementById('rUptime');
  if(!latencyEl || !nodesEl || !uptimeEl) return;

  // Edit these three placeholder values to your own numbers.
  latencyEl.textContent = '4+';
  nodesEl.textContent = '20+';
  uptimeEl.textContent = 'OPEN TO WORK';
}

/* ---------------------------------------------------------
   Scroll reveal for cards / sections
--------------------------------------------------------- */
function initScrollReveal(){
  const targets = document.querySelectorAll('.feature-card, .process__item, .stat, .testimonial, .section-head, .about__content, .about__avatar-wrap, .skills__group');
  targets.forEach(el => {
    el.style.opacity = '0';
    el.style.transform = 'translateY(16px)';
    el.style.transition = 'opacity 0.7s ease, transform 0.7s ease';
  });

  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if(entry.isIntersecting){
        entry.target.style.opacity = '1';
        entry.target.style.transform = 'translateY(0)';
        observer.unobserve(entry.target);
      }
    });
  }, { threshold: 0.15 });

  targets.forEach(el => observer.observe(el));
}

/* ---------------------------------------------------------
   Animated stat counters
--------------------------------------------------------- */
function initStatCounters(){
  const stats = document.querySelectorAll('.stat__value');
  if(!stats.length) return;

  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if(entry.isIntersecting){
        animateCount(entry.target);
        observer.unobserve(entry.target);
      }
    });
  }, { threshold: 0.4 });

  stats.forEach(el => observer.observe(el));
}

function animateCount(el){
  const target = parseFloat(el.getAttribute('data-count'));
  const decimals = parseInt(el.getAttribute('data-decimals') || '0', 10);
  const duration = 1400;
  const start = performance.now();

  function frame(now){
    const progress = Math.min((now - start) / duration, 1);
    const eased = 1 - Math.pow(1 - progress, 3);
    const value = target * eased;
    el.textContent = decimals > 0 ? value.toFixed(decimals) : Math.round(value).toLocaleString();
    if(progress < 1){
      requestAnimationFrame(frame);
    } else {
      el.textContent = decimals > 0 ? target.toFixed(decimals) : target.toLocaleString();
    }
  }
  requestAnimationFrame(frame);
}

/* ---------------------------------------------------------
   Contact form (front-end only demo — wire up to a real
   backend, Formspree, or mailto: link before going live)
--------------------------------------------------------- */
function initCtaForm(){
  const form = document.getElementById('ctaForm');
  const note = document.getElementById('ctaNote');
  if(!form || !note) return;

  form.addEventListener('submit', (e) => {
    e.preventDefault();
    const nameField = document.getElementById('ctaName');
    const email = document.getElementById('ctaEmail').value.trim();
    const name = nameField ? nameField.value.trim() : '';

    if(!email){
      note.textContent = 'Enter your email so I can reply.';
      note.style.color = '#ff8b8b';
      return;
    }
    note.textContent = name
      ? `✓ Thanks, ${name} — message received. I'll reply soon.`
      : `✓ Message received. I'll reply soon.`;
    note.style.color = 'var(--accent-2)';
    form.reset();
  });
}

/* ---------------------------------------------------------
   Back to top button
--------------------------------------------------------- */
function initToTop(){
  const btn = document.getElementById('toTop');
  if(!btn) return;

  window.addEventListener('scroll', debounce(() => {
    if(window.scrollY > 700){
      btn.classList.add('visible');
    } else {
      btn.classList.remove('visible');
    }
  }, 100));

  btn.addEventListener('click', () => {
    window.scrollTo({ top: 0, behavior: 'smooth' });
  });
}
