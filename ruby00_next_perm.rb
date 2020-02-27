require 'pry'
require 'awesome_print'

def fac(n)
  (1..n).inject(1, &:*)
end

def next_perm(xs, n)
  i = n - 2
  i -= 1 while i >= 0 && xs[i] > xs[i + 1]
  return if i == -1
  j = i + 1
  j += 1 while j < n && xs[j] >= xs[i]
  j -= 1
  tmp = xs[i]
  xs[i] = xs[j]
  xs[j] = tmp
  i += 1
  j = n - 1
  while i < j
    tmp = xs[i]
    xs[i] = xs[j]
    xs[j] = tmp
    i += 1
    j -= 1
  end
  xs
end

def wife(n, k)
  return 0.0 if n == 0
  return 1.0 if n == 1
  k = [k, n - 1].min
  seq = n.times.map.to_a
  result = 0
  while seq
    i = 0
    best = -1
    while i < k
      best = seq[i] if best < seq[i]
      i += 1
    end
    i += 1 while i < n && seq[i] <= best
    result += 1 if seq[i] == n - 1
    seq = next_perm(seq, n)
  end
  denom = fac(n)
  (result.to_f / denom).round(3)
end

def best_wife(n)
  values = n.times.map { |k| wife(n, k) }
  idx = values.index(values.max)
  [n, idx, values[idx], values]
end

def measure
  time_start = Time.now
  result = yield
  time_end = Time.now
  [result, time_end - time_start]
end

(1..10).each do |n|
  p measure { best_wife(n) }
end
